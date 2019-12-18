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
struct addrnode {struct addredge** edge; struct addredge* parent_edge; } ;
struct addredge {int len; int parent_index; int /*<<< orphan*/ * str; struct addrnode* parent_node; struct addrnode* node; } ;
typedef  int addrlen_t ;
typedef  int /*<<< orphan*/  addrkey_t ;

/* Variables and functions */
 int KEYWIDTH ; 
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/  free (struct addredge*) ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static struct addredge * 
edge_create(struct addrnode *node, const addrkey_t *addr, 
	addrlen_t addrlen, struct addrnode *parent_node, int parent_index)
{
	size_t n;
	struct addredge *edge = (struct addredge *)malloc( sizeof (*edge) );
	if (!edge)
		return NULL;
	edge->node = node;
	edge->len = addrlen;
	edge->parent_index = parent_index;
	edge->parent_node = parent_node;
	/* ceil() */
	n = (size_t)((addrlen / KEYWIDTH) + ((addrlen % KEYWIDTH != 0)?1:0));
	edge->str = (addrkey_t *)calloc(n, sizeof (addrkey_t));
	if (!edge->str) {
		free(edge);
		return NULL;
	}
	memcpy(edge->str, addr, n * sizeof (addrkey_t));
	/* Only manipulate other objects after successful alloc */
	node->parent_edge = edge;
	log_assert(parent_node->edge[parent_index] == NULL);
	parent_node->edge[parent_index] = edge;
	return edge;
}