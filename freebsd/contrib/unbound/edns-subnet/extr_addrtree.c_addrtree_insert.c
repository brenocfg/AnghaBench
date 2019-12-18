#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ time_t ;
struct addrtree {scalar_t__ max_depth; int /*<<< orphan*/  size_bytes; int /*<<< orphan*/  node_count; scalar_t__ (* sizefunc ) (void*) ;struct addrnode* root; } ;
struct addrnode {scalar_t__ ttl; scalar_t__ scope; void* elem; struct addredge** edge; } ;
struct addredge {scalar_t__ len; int parent_index; struct addrnode* parent_node; int /*<<< orphan*/  const* str; struct addrnode* node; } ;
typedef  scalar_t__ addrlen_t ;
typedef  int /*<<< orphan*/  addrkey_t ;

/* Variables and functions */
 scalar_t__ bits_common (int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  clean_node (struct addrtree*,struct addrnode*) ; 
 int /*<<< orphan*/  edge_create (struct addrnode*,int /*<<< orphan*/  const*,scalar_t__,struct addrnode*,int) ; 
 int /*<<< orphan*/  free (struct addrnode*) ; 
 int getbit (int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  lru_cleanup (struct addrtree*) ; 
 int /*<<< orphan*/  lru_push (struct addrtree*,struct addrnode*) ; 
 struct addrnode* node_create (struct addrtree*,void*,scalar_t__,scalar_t__) ; 
 scalar_t__ node_size (struct addrtree*,struct addrnode*) ; 
 int /*<<< orphan*/  purge_node (struct addrtree*,struct addrnode*) ; 
 scalar_t__ stub1 (void*) ; 

void
addrtree_insert(struct addrtree *tree, const addrkey_t *addr, 
	addrlen_t sourcemask, addrlen_t scope, void *elem, time_t ttl, 
	time_t now)
{
	struct addrnode *newnode, *node;
	struct addredge *edge;
	int index;
	addrlen_t common, depth;

	node = tree->root;
	log_assert(node != NULL);

	/* Protect our cache against too much fine-grained data */
	if (tree->max_depth < scope) scope = tree->max_depth;
	/* Server answer was less specific than question */
	if (scope < sourcemask) sourcemask = scope;

	depth = 0;
	while (1) {
		log_assert(depth <= sourcemask);
		/* Case 1: update existing node */
		if (depth == sourcemask) {
			/* update this node's scope and data */
			clean_node(tree, node);
			node->ttl = ttl;
			node->elem = elem;
			node->scope = scope;
			tree->size_bytes += tree->sizefunc(elem);
			return;
		}
		index = getbit(addr, sourcemask, depth);
		/* Get an edge to an unexpired node */
		edge = node->edge[index];
		while (edge) {
			/* Purge all expired nodes on path */
			if (!edge->node->elem || edge->node->ttl >= now)
				break;
			purge_node(tree, edge->node);
			edge = node->edge[index];
		}
		/* Case 2: New leafnode */
		if (!edge) {
			newnode = node_create(tree, elem, scope, ttl);
			if (!newnode) return;
			if (!edge_create(newnode, addr, sourcemask, node,
				index)) {
				clean_node(tree, newnode);
				tree->node_count--;
				free(newnode);
				return;
			}
			tree->size_bytes += node_size(tree, newnode);
			lru_push(tree, newnode);
			lru_cleanup(tree);
			return;
		}
		/* Case 3: Traverse edge */
		common = bits_common(edge->str, edge->len, addr, sourcemask,
			depth);
		if (common == edge->len) {
			/* We update the scope of intermediate nodes. Apparently
			 * the * authority changed its mind. If we would not do
			 * this we might not be able to reach our new node. */
			node->scope = scope;
			depth = edge->len;
			node = edge->node;
			continue;
		}
		/* Case 4: split. */
		if (!(newnode = node_create(tree, NULL, 0, 0)))
			return;
		node->edge[index] = NULL;
		if (!edge_create(newnode, addr, common, node, index)) {
			node->edge[index] = edge;
			clean_node(tree, newnode);
			tree->node_count--;
			free(newnode);
			return;
		}
		lru_push(tree, newnode);
		/* connect existing child to our new node */
		index = getbit(edge->str, edge->len, common);
		newnode->edge[index] = edge;
		edge->parent_node = newnode;
		edge->parent_index = (int)index;
		
		if (common == sourcemask) {
			/* Data is stored in the node */
			newnode->elem = elem;
			newnode->scope = scope;
			newnode->ttl = ttl;
		} 
		
		tree->size_bytes += node_size(tree, newnode);

		if (common != sourcemask) {
			/* Data is stored in other leafnode */
			node = newnode;
			newnode = node_create(tree, elem, scope, ttl);
			if (!edge_create(newnode, addr, sourcemask, node,
				index^1)) {
				clean_node(tree, newnode);
				tree->node_count--;
				free(newnode);
				return;
			}
			tree->size_bytes += node_size(tree, newnode);
			lru_push(tree, newnode);
		}
		lru_cleanup(tree);
		return;
	}
}