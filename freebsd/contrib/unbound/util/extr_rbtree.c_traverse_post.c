#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* right; struct TYPE_6__* left; } ;
typedef  TYPE_1__ rbnode_type ;

/* Variables and functions */
 TYPE_1__* RBTREE_NULL ; 
 void stub1 (TYPE_1__*,void*) ; 

__attribute__((used)) static void 
traverse_post(void (*func)(rbnode_type*, void*), void* arg, rbnode_type* node)
{
	if(!node || node == RBTREE_NULL)
		return;
	/* recurse */
	traverse_post(func, arg, node->left);
	traverse_post(func, arg, node->right);
	/* call user func */
	(*func)(node, arg);
}