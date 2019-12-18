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
struct ttm_buffer_object {TYPE_1__* vm_node; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */

int
ttm_bo_cmp_rb_tree_items(struct ttm_buffer_object *a,
    struct ttm_buffer_object *b)
{

	if (a->vm_node->start < b->vm_node->start) {
		return (-1);
	} else if (a->vm_node->start > b->vm_node->start) {
		return (1);
	} else {
		return (0);
	}
}