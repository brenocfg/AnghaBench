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
struct rbtree_type {int dummy; } ;
struct respip_set {struct rbtree_type ip_tree; } ;

/* Variables and functions */

struct rbtree_type*
respip_set_get_tree(struct respip_set* set)
{
	if(!set)
		return NULL;
	return &set->ip_tree;
}