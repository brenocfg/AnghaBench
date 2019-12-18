#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct TYPE_2__ {struct addr_tree_node* key; } ;
struct addr_tree_node {int net; TYPE_1__ node; int /*<<< orphan*/ * parent; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  rbtree_type ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rbtree_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

int addr_tree_insert(rbtree_type* tree, struct addr_tree_node* node,
        struct sockaddr_storage* addr, socklen_t addrlen, int net)
{
	node->node.key = node;
	memcpy(&node->addr, addr, addrlen);
	node->addrlen = addrlen;
	node->net = net;
	node->parent = NULL;
	return rbtree_insert(tree, &node->node) != NULL;
}