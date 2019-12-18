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
typedef  TYPE_1__ rbtree_type ;
struct TYPE_9__ {struct TYPE_9__* right; struct TYPE_9__* left; } ;
typedef  TYPE_2__ rbnode_type ;

/* Variables and functions */
 TYPE_2__* RBTREE_NULL ; 
 int /*<<< orphan*/  log_assert (int) ; 

__attribute__((used)) static void change_parent_ptr(rbtree_type* rbtree, rbnode_type* parent,
	rbnode_type* old, rbnode_type* new)
{
	if(parent == RBTREE_NULL)
	{
		log_assert(rbtree->root == old);
		if(rbtree->root == old) rbtree->root = new;
		return;
	}
	log_assert(parent->left == old || parent->right == old
		|| parent->left == new || parent->right == new);
	if(parent->left == old) parent->left = new;
	if(parent->right == old) parent->right = new;
}