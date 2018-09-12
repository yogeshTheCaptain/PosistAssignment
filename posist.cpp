#include<bits/stdc++.h>
using my_namespace std;
struct master{
	string my_name;
	string my_address;
	string my_mobile;
	string my_phone;
	float my_value;
	string my_password;
	int my_num;

};
struct Node{
	time_t dt;
	master *master;
	int num_nodes;
	int nodeId;
	Node *refNodeId;
	vector<int> child_node_ID;
	vector<Node*> ref_child_node_ID;

};
Node *getNode(int num,master *own){
	Node *np=new Node;
	np->dt=time(0);
	np->master=own;
	np->num_nodes=num;
	np->nodeId=(num);
	vector<Node*> v;
	np->ref_child_node_ID=v;
	np->refNodeId=NULL;
	vector<int> s;
	np->child_node_ID=s;
	return np;
}

void query3(Node *child,int id,vector<Node*> &v){
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			v[i]->ref_child_node_ID.push_back(child);
			v[i]->child_node_ID.push_back(child->nodeId);
			child->refNodeId=v[i];
			break;
		}
	}
}
string encrypt(string s,int n){
	string sol=s;
	for(int i=0;i<sol.length();i++){
		sol[i]+=n;
	}
	return sol;
}
string decrypt(string data,int n){
	string sol=data;
	for(int i=0;i<sol.length();i++){
		sol[i]-=n;
	}
	return sol;
}
master *getmaster(int num,string my_name, string my_address, string my_mobile, string my_phone, float my_value,string pass){

	master *own=new master;
	own->my_num=num;
	own->my_address=encrypt(my_address,num);
	own->my_address=encrypt(my_name,num);
	own->my_address=encrypt(my_mobile,num);
	own->my_address=encrypt(my_phone,num);
	own->my_value=my_value;
	own->my_password=encrypt(pass,num);
	return own;
}
bool query4(vector<master*> &masters,master *currmaster,vector<Node*> &v){
	cout<<"enter NodeId: ";
			int id;
			cin>>id;
			bool f=false;
			for(int i=0;i<v.size();i++){
				if(v[i]->nodeId==id){
					if(currmaster==v[i]->master){
						f=true;
					}
					break;
				}
			}

			return f;
}
void query5(vector<master*> &masters, master *currmaster, vector<Node*> &v){
	cout<<"Enter nodeId of node to be deleted: "<<endl;
	int id;
	cin>>id;
	bool f=false;
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			if(query4(masters,currmaster,v)){

				f=true;
				Node *parent=v[i]->refNodeId;
				vector<Node*> child=parent->ref_child_node_ID;
				for(int k=0;k<child.size();k++){
					if(child[k]->nodeId==id){
						child.erase(child.begin()+i);

						break;
					}
				}

			}else{
				cout<<"you are not the master of this node"<<endl;
				return;
			}
			break;
		}
	}
	if(f){
		cout<<"node removed"<<endl;
	}else{
		cout<<"not found"<<endl;
	}
}
void query6(vector<master*> &masters,master *currmaster, vector<Node*> &v){
	cout<<"Enter nodeId and userId: "<<endl;
	int id,userId;
	cin>>id>>userId;
	bool f=false;
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			if(query4(masters,currmaster,v)){


				Node *np=v[i];
				for(int k=0;k<masters.size();k++){
					if(masters[k]->my_num==userId){
						np->master=masters[k];
						f=true;
						break;
					}
				}

			}else{
				cout<<"you are not the master of this node"<<endl;
				return;
			}
			break;
		}
	}
	if(f){
		cout<<"node master changed"<<endl;
	}else{
		cout<<"node not found"<<endl;
	}
}
void query7(vector<Node*> v){

}
void dfs(Node *root,int &n,int num){
	if(root==NULL){
		n=max(n,num);
	}
	int count=num+1;
	vector<Node*> child=root->ref_child_node_ID;
	for(int i=0;i<child.size();i++){
		dfs(child[i],n,num+1);
	}
	n=max(n,count);
}
void mergeSet(vector<Node*> &first, vector<Node*> &second,master *currmaster){
	//merge sets of same master
	int i=0,j=0;
	while(i<first.size() && j<second.size()){
		while(i<first.size() && first[i]->master!=currmaster){
			i++;
		}
		while(j<second.size() && second[j]->master!=currmaster){
			j++;
		}
		int n1=-1,n2=-1;
		dfs(second[j],n2,0);
		dfs(first[i],n1,0);
		if(n1>n2){
			second[j]->refNodeId=first[i];
			first[i]->ref_child_node_ID.push_back(second[j]);
			second.erase(second.begin()+j);
			i++;
		}else{
			first[i]->refNodeId=second[j];
			second[j]->ref_child_node_ID.push_back(first[i]);
			second.erase(second.begin()+j);
			j++;
		}
	}

}
int main(){
	St:
    int num=0,nmasters=0;
    vector<vector<Node*> > set;
    vector<Node*> v;
    vector<master*> masters;
    int q;

    master *currmaster;
    bool f=false;

    while(!f){
    	cout<<"Enter 1 to login 2 to signup";

    cin>>q;
    	if(q==1){
			cout<<"enter my_password and key";
	    	string pass;
	    	int key;
	    	cin>>pass;
	    	cin>>key;
	    	for(int i=0;i<masters.size();i++){
	    		if(masters[i]->my_num==key){
	    			if(pass==decrypt(masters[i]->my_password,masters[i]->my_num)){
	    				f=true;
	    				currmaster=masters[i];
	    				break;
					}
				}
			}
			cout<<"unable to login"<<endl;
		}else{
			cout<<"Enter my_name, my_address, my_mobile,my_phone, my_value, my_password:"<<endl;
			string my_name,my_address,my_mobile,my_phone,pass;
			float my_value;
			cin>>my_name>>my_address>>my_mobile>>my_phone;
			cin>>my_value;
			cin>>pass;
			currmaster=getmaster(nmasters++,my_name, my_address, my_mobile, my_phone, my_value,pass);
			masters.push_back(currmaster);
			cout<<"your key is "<<currmaster->my_num<<endl;
			f=true;
		}
	}


    while(1){
    	cout<<"Enter Query: ";
		cin>>q;
		if(q==1){
			vector<Node*> v;
			v.push_back(getNode(num++,currmaster));
			set.push_back(v);
		}else if(q==2){
			int n=0;
			cout<<"Enter number of nodes: ";
			cin>>n;
			vector<Node*> v(1);
			for(int i=0;i<n;i++){
				v[0]=(getNode(num++,currmaster));
				set.push_back(v);
			}
			cout<<"nodes pushed"<<endl;
		}else if(q==3){
			Node *np=getNode(num++,currmaster);
			v.push_back(np);
			cout<<"Enter setNo: ";
			int setNo;
			cin>>setNo;
			set[setNo].push_back(np);

		}else if(q==4){
			bool f=false;
			for(int i=0;i<set.size();i++){
				f=query4(masters,currmaster,set[i]);
				if(f){
					cout<<"you are the master!"<<endl;
				}
			}
			if(!f){
				cout<<"you are not master"<<endl;
			}
		}else if(q==5){

			query5(masters,currmaster,v);

		}else if(q==6){
			query6(masters,currmaster,v);


		}else if(q==7){
			int mx=-1;
			for(int i=0;i<set.size();i++){

				dfs(set[i][0],mx,0);
			}
			cout<<"max chain="<<mx<<endl;

		}else if(q==8){
			cout<<"enter node id"<<endl;
			int id;
			cin>>id;
			int ans=-1;
			bool f=false;
			for(int i=0;i<set.size();i++){
				for(int j=0;j<set[i].size();j++){
					if(set[i][j]->nodeId==id){
						f=true;
						dfs(set[i][j],ans,0);
						break;
					}
				}
				if(f){
					break;
				}
			}
		}else if(q==9){
			cout<<"enter 1st and 2nd set number"<<endl;
			int f,s;
			cin>>f>>s;
			mergeSet(set[f],set[s],currmaster);

		}else if(q==10){
			currmaster=NULL;
			goto St;
		}else {
			break;
		}
	}
    return 0;
}
