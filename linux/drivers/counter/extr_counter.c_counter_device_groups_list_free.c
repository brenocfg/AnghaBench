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
struct TYPE_2__ {struct counter_device_attr_group* const attrs; struct counter_device_attr_group* const name; } ;
struct counter_device_attr_group {int /*<<< orphan*/  attr_list; TYPE_1__ attr_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  counter_device_attr_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct counter_device_attr_group* const) ; 

__attribute__((used)) static void counter_device_groups_list_free(
	struct counter_device_attr_group *const groups_list,
	const size_t num_groups)
{
	struct counter_device_attr_group *group;
	size_t i;

	/* loop through all attribute groups (signals, counts, global, etc.) */
	for (i = 0; i < num_groups; i++) {
		group = groups_list + i;

		/* free all attribute group and associated attributes memory */
		kfree(group->attr_group.name);
		kfree(group->attr_group.attrs);
		counter_device_attr_list_free(&group->attr_list);
	}

	kfree(groups_list);
}