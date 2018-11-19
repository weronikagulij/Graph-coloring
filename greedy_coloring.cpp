#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Graph {
    int V; // number of vertices
    int E; // current number of edges
    vector<long long> vList[10000]; // list of vertices

public:
    Graph(int V);
    void addEdge(int a, int b);
    void writeEdges();
    void greedyColoring();
};

Graph::Graph(int V) {
    this->V = V;
    this->E = 0;
}

void Graph::addEdge(int a, int b) {
    vList[a].push_back(b);
    vList[b].push_back(a);
    E++;
}

void Graph::writeEdges() {
    for(int i = 0; i < V; i++) {
        cout<<"Vertex nr "<<i<<": ";
        for(int j = 0; j < vList[i].size(); j++) {
            cout<<vList[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"Liczba krawedzi: "<<E<<endl;
}

void Graph::greedyColoring() {
    bool availableColors[V+1]; // availableColors[2] == 0 means that color nr 2 is not available for tested vertex

    int colors[V+1]; // which colors have vertices

    for(int i = 0; i < V; i++) {
        colors[i] = -1;
    }
    colors[0] = 0; // first vertex has the color number 0

    for(int i = 1; i < V; i++) { // choose color for each vertex
       // every color is available at the beginning
        for(int j = 0; j < V; j++) {
            availableColors[j] = 1;
        }

        // if there is any colored vertex connected to the "i" one with edge, sign it in availableColors array
        // colors[x] == -1 means that there is no assigned color to x vertex
        for(int j = 0; j < vList[i].size(); j++) {
            if(colors[vList[i][j]] != -1) {
                availableColors[colors[vList[i][j]]] = 0;
            }
        }
        //////
        for(int j = 0; j < V; j++) {
            if(availableColors[j] == 1) {
                colors[i] = j;
                break;
            }
        }

    }

    // find max nr of color
    int maximum = -1;
    for (int i = 0; i < V; i ++ ) {
        if(colors[i] > maximum) maximum = colors[i];
    }

    cout << "To color this graph we need: " << maximum+1 << " colors."<<endl;
}

Graph edgesFromConsole() {
    int numberOfEdges, a, b, numberOfVertex;

    cout << "Number of vertices: ";
    cin >> numberOfVertex;

    Graph g(numberOfVertex);

    cout << endl << "Number of edges: ";
    cin >> numberOfEdges;

    cout << endl << "Edges: ";
    for(int i = 0; i < numberOfEdges; i++) {
        cin >> a >> b;
        g.addEdge(a, b);
    }

    return g;
}

Graph edgesFromFile() {
    int numberOfVertex, numberOfEdges, a, b;
    fstream file;
    file.open("dane.txt", ios::in);

    file >> numberOfVertex;

    Graph g(numberOfVertex);

    while(!file.eof()) {
         file >> a >> b;
         g.addEdge(a, b);
    }
    file.close();
    return g;
}

int main()
{
    Graph g = edgesFromFile();
    //Graph g = edgesFromConsole();

    //g.writeEdges();
    g.greedyColoring();
    return 0;
}
