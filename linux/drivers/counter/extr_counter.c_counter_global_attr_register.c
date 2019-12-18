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
struct counter_device_attr_group {int /*<<< orphan*/  attr_list; } ;
struct counter_device {int /*<<< orphan*/  num_signals; int /*<<< orphan*/  num_counts; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  counter_device_attr_list_free (int /*<<< orphan*/ *) ; 
 int counter_device_ext_register (struct counter_device_attr_group* const,struct counter_device* const) ; 
 int counter_name_attribute_create (struct counter_device_attr_group* const,int /*<<< orphan*/ ) ; 
 int counter_size_attribute_create (struct counter_device_attr_group* const,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int counter_global_attr_register(
	struct counter_device_attr_group *const group,
	struct counter_device *const counter)
{
	int err;

	/* Create name attribute */
	err = counter_name_attribute_create(group, counter->name);
	if (err)
		return err;

	/* Create num_counts attribute */
	err = counter_size_attribute_create(group, counter->num_counts,
					    "num_counts");
	if (err)
		goto err_free_attr_list;

	/* Create num_signals attribute */
	err = counter_size_attribute_create(group, counter->num_signals,
					    "num_signals");
	if (err)
		goto err_free_attr_list;

	/* Register Counter device extension attributes */
	err = counter_device_ext_register(group, counter);
	if (err)
		goto err_free_attr_list;

	return 0;

err_free_attr_list:
	counter_device_attr_list_free(&group->attr_list);
	return err;
}