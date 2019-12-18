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
typedef  TYPE_1__ ldns_rbnode_t ;

/* Variables and functions */
 TYPE_1__* LDNS_RBTREE_NULL ; 

__attribute__((used)) static void change_child_ptr(ldns_rbnode_t* child, ldns_rbnode_t* old, ldns_rbnode_t* new)
{
	if(child == LDNS_RBTREE_NULL) return;
	if(child->parent == old) child->parent = new;
}