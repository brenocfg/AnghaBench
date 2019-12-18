#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtree_entry {TYPE_2__* dir_info; } ;
struct TYPE_3__ {struct mtree_entry** last; } ;
struct TYPE_4__ {struct mtree_entry* chnext; TYPE_1__ children; } ;

/* Variables and functions */

__attribute__((used)) static int
mtree_entry_add_child_tail(struct mtree_entry *parent,
    struct mtree_entry *child)
{
	child->dir_info->chnext = NULL;
	*parent->dir_info->children.last = child;
	parent->dir_info->children.last = &(child->dir_info->chnext);
	return (1);
}