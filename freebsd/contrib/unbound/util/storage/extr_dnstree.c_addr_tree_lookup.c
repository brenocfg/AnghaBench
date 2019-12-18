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
struct addr_tree_node {scalar_t__ addrlen; int net; struct addr_tree_node* parent; int /*<<< orphan*/  addr; TYPE_1__ node; } ;
typedef  scalar_t__ socklen_t ;
typedef  int /*<<< orphan*/  rbtree_type ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int addr_in_common (int /*<<< orphan*/ *,int,struct sockaddr_storage*,int,scalar_t__) ; 
 scalar_t__ addr_is_ip6 (struct sockaddr_storage*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_storage*,scalar_t__) ; 
 scalar_t__ rbtree_find_less_equal (int /*<<< orphan*/ *,struct addr_tree_node*,int /*<<< orphan*/ **) ; 

struct addr_tree_node* addr_tree_lookup(rbtree_type* tree, 
        struct sockaddr_storage* addr, socklen_t addrlen)
{
        rbnode_type* res = NULL;
        struct addr_tree_node* result;
        struct addr_tree_node key;
        key.node.key = &key;
        memcpy(&key.addr, addr, addrlen);
        key.addrlen = addrlen;
        key.net = (addr_is_ip6(addr, addrlen)?128:32);
        if(rbtree_find_less_equal(tree, &key, &res)) {
                /* exact */
                return (struct addr_tree_node*)res;
        } else {
                /* smaller element (or no element) */
                int m;
                result = (struct addr_tree_node*)res;
                if(!result || result->addrlen != addrlen)
                        return 0;
                /* count number of bits matched */
                m = addr_in_common(&result->addr, result->net, addr,
                        key.net, addrlen);
                while(result) { /* go up until addr is inside netblock */
                        if(result->net <= m)
                                break;
                        result = result->parent;
                }
        }
        return result;
}