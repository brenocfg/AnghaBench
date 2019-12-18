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
struct addr_tree_node {int net; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; TYPE_1__ node; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  rbtree_type ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rbtree_search (int /*<<< orphan*/ *,struct addr_tree_node*) ; 

struct addr_tree_node* addr_tree_find(rbtree_type* tree,
        struct sockaddr_storage* addr, socklen_t addrlen, int net)
{
        rbnode_type* res = NULL;
        struct addr_tree_node key;
        key.node.key = &key;
        memcpy(&key.addr, addr, addrlen);
        key.addrlen = addrlen;
        key.net = net;
	res = rbtree_search(tree, &key);
	return (struct addr_tree_node*)res;
}