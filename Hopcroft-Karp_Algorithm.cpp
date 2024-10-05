#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define NIL 0
#define INF (1<<28)

vector<vector<int>> adj;
vector<int> pairU, pairV, dist;

bool bfs(int m) {
    queue<int> Q;
    for (int u = 1; u <= m; ++u) {
        if (pairU[u] == NIL) {
            dist[u] = 0;
            Q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[NIL] = INF;

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        if (dist[u] < dist[NIL]) {
            for (int v : adj[u]) {
                if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    Q.push(pairV[v]);
                }
            }
        }
    }
    return dist[NIL] != INF;
}

bool dfs(int u) {
    if (u != NIL) {
        for (int v : adj[u]) {
            if (dist[pairV[v]] == dist[u] + 1) {
                if (dfs(pairV[v])) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroftKarp(int m, int n) {
    pairU.assign(m + 1, NIL);
    pairV.assign(n + 1, NIL);
    dist.assign(m + 1, 0);

    int matching = 0;
    while (bfs(m)) {
        for (int u = 1; u <= m; ++u) {
            if (pairU[u] == NIL && dfs(u)) {
                matching++;
            }
        }
    }
    return matching;
}

int main() {
    int m, n, edges;
    cout << "Enter number of vertices in set U and V: ";
    cin >> m >> n;
    adj.resize(m + 1);

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    int maxMatching = hopcroftKarp(m, n);
    cout << "Maximum Matching: " << maxMatching << endl;

    return 0;
}
