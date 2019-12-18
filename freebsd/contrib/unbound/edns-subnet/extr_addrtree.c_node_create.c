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
typedef  int /*<<< orphan*/  time_t ;
struct addrtree {int /*<<< orphan*/  node_count; } ;
struct addrnode {int /*<<< orphan*/ * prev; int /*<<< orphan*/ * next; int /*<<< orphan*/ * parent_edge; int /*<<< orphan*/ ** edge; int /*<<< orphan*/  ttl; int /*<<< orphan*/  scope; void* elem; } ;
typedef  int /*<<< orphan*/  addrlen_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

__attribute__((used)) static struct addrnode * 
node_create(struct addrtree *tree, void *elem, addrlen_t scope, 
	time_t ttl)
{
	struct addrnode* node = (struct addrnode *)malloc( sizeof (*node) );
	if (!node)
		return NULL;
	node->elem = elem;
	tree->node_count++;
	node->scope = scope;
	node->ttl = ttl;
	node->edge[0] = NULL;
	node->edge[1] = NULL;
	node->parent_edge = NULL;
	node->next = NULL;
	node->prev = NULL;
	return node;
}