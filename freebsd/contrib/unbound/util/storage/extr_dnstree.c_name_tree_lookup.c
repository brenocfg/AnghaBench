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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {struct name_tree_node* key; } ;
struct name_tree_node {size_t len; int labs; scalar_t__ dclass; struct name_tree_node* parent; int /*<<< orphan*/ * name; TYPE_1__ node; } ;
typedef  int /*<<< orphan*/  rbtree_type ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int /*<<< orphan*/  dname_lab_cmp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ rbtree_find_less_equal (int /*<<< orphan*/ *,struct name_tree_node*,int /*<<< orphan*/ **) ; 

struct name_tree_node* name_tree_lookup(rbtree_type* tree, uint8_t* name,
        size_t len, int labs, uint16_t dclass)
{
        rbnode_type* res = NULL;
        struct name_tree_node *result;
        struct name_tree_node key;
        key.node.key = &key;
        key.name = name;
        key.len = len;
        key.labs = labs;
        key.dclass = dclass;
        if(rbtree_find_less_equal(tree, &key, &res)) {
                /* exact */
                result = (struct name_tree_node*)res;
        } else {
                /* smaller element (or no element) */
                int m;
                result = (struct name_tree_node*)res;
                if(!result || result->dclass != dclass)
                        return NULL;
                /* count number of labels matched */
                (void)dname_lab_cmp(result->name, result->labs, key.name,
                        key.labs, &m);
                while(result) { /* go up until qname is subdomain of stub */
                        if(result->labs <= m)
                                break;
                        result = result->parent;
                }
        }
	return result;
}