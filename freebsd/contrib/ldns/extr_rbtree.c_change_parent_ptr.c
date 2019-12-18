#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* root; } ;
typedef  TYPE_1__ ldns_rbtree_t ;
struct TYPE_9__ {struct TYPE_9__* right; struct TYPE_9__* left; } ;
typedef  TYPE_2__ ldns_rbnode_t ;

/* Variables and functions */
 TYPE_2__* LDNS_RBTREE_NULL ; 

__attribute__((used)) static void change_parent_ptr(ldns_rbtree_t* rbtree, ldns_rbnode_t* parent, ldns_rbnode_t* old, ldns_rbnode_t* new)
{
	if(parent == LDNS_RBTREE_NULL)
	{
		if(rbtree->root == old) rbtree->root = new;
		return;
	}
	if(parent->left == old) parent->left = new;
	if(parent->right == old) parent->right = new;
}