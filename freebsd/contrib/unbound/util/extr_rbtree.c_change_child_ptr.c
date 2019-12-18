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
struct TYPE_6__ {struct TYPE_6__* parent; } ;
typedef  TYPE_1__ rbnode_type ;

/* Variables and functions */
 TYPE_1__* RBTREE_NULL ; 
 int /*<<< orphan*/  log_assert (int) ; 

__attribute__((used)) static void change_child_ptr(rbnode_type* child, rbnode_type* old,
	rbnode_type* new)
{
	if(child == RBTREE_NULL) return;
	log_assert(child->parent == old || child->parent == new);
	if(child->parent == old) child->parent = new;
}