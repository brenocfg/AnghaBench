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
struct counter_device_attr_group {int /*<<< orphan*/  attr_list; } ;
struct counter_device {int num_signals; int num_counts; TYPE_1__* device_state; } ;
struct TYPE_2__ {size_t num_groups; struct counter_device_attr_group* groups_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int counter_counts_register (struct counter_device_attr_group*,struct counter_device* const) ; 
 int /*<<< orphan*/  counter_device_groups_list_free (struct counter_device_attr_group*,size_t) ; 
 int counter_global_attr_register (struct counter_device_attr_group*,struct counter_device* const) ; 
 int counter_signals_register (struct counter_device_attr_group*,struct counter_device* const) ; 
 struct counter_device_attr_group* kcalloc (size_t const,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int counter_device_groups_list_prepare(
	struct counter_device *const counter)
{
	const size_t total_num_groups =
		counter->num_signals + counter->num_counts + 1;
	struct counter_device_attr_group *groups_list;
	size_t i;
	int err;
	size_t num_groups = 0;

	/* Allocate space for attribute groups (signals, counts, and ext) */
	groups_list = kcalloc(total_num_groups, sizeof(*groups_list),
			      GFP_KERNEL);
	if (!groups_list)
		return -ENOMEM;

	/* Initialize attribute lists */
	for (i = 0; i < total_num_groups; i++)
		INIT_LIST_HEAD(&groups_list[i].attr_list);

	/* Register Signals */
	err = counter_signals_register(groups_list, counter);
	if (err)
		goto err_free_groups_list;
	num_groups += counter->num_signals;

	/* Register Counts and respective Synapses */
	err = counter_counts_register(groups_list + num_groups, counter);
	if (err)
		goto err_free_groups_list;
	num_groups += counter->num_counts;

	/* Register Counter global attributes */
	err = counter_global_attr_register(groups_list + num_groups, counter);
	if (err)
		goto err_free_groups_list;
	num_groups++;

	/* Store groups_list in device_state */
	counter->device_state->groups_list = groups_list;
	counter->device_state->num_groups = num_groups;

	return 0;

err_free_groups_list:
	counter_device_groups_list_free(groups_list, num_groups);
	return err;
}