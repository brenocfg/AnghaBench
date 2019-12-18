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
struct counter_signal_unit {struct counter_signal* signal; } ;
struct counter_signal {int /*<<< orphan*/  name; } ;
struct counter_device_attr_group {int /*<<< orphan*/  attr_list; } ;
struct counter_device {TYPE_1__* ops; } ;
struct counter_attr_parm {char* prefix; char* name; struct counter_signal_unit* component; int /*<<< orphan*/ * store; int /*<<< orphan*/ * show; struct counter_device_attr_group* group; } ;
struct TYPE_2__ {scalar_t__ signal_read; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int counter_attribute_create (struct counter_attr_parm*) ; 
 int /*<<< orphan*/  counter_device_attr_list_free (int /*<<< orphan*/ *) ; 
 int counter_name_attribute_create (struct counter_device_attr_group* const,int /*<<< orphan*/ ) ; 
 int counter_signal_ext_register (struct counter_device_attr_group* const,struct counter_signal* const) ; 
 int /*<<< orphan*/ * counter_signal_show ; 
 int /*<<< orphan*/  kfree (struct counter_signal_unit*) ; 
 struct counter_signal_unit* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int counter_signal_attributes_create(
	struct counter_device_attr_group *const group,
	const struct counter_device *const counter,
	struct counter_signal *const signal)
{
	struct counter_signal_unit *signal_comp;
	struct counter_attr_parm parm;
	int err;

	/* Allocate Signal attribute component */
	signal_comp = kmalloc(sizeof(*signal_comp), GFP_KERNEL);
	if (!signal_comp)
		return -ENOMEM;
	signal_comp->signal = signal;

	/* Create main Signal attribute */
	parm.group = group;
	parm.prefix = "";
	parm.name = "signal";
	parm.show = (counter->ops->signal_read) ? counter_signal_show : NULL;
	parm.store = NULL;
	parm.component = signal_comp;
	err = counter_attribute_create(&parm);
	if (err) {
		kfree(signal_comp);
		return err;
	}

	/* Create Signal name attribute */
	err = counter_name_attribute_create(group, signal->name);
	if (err)
		goto err_free_attr_list;

	/* Register Signal extension attributes */
	err = counter_signal_ext_register(group, signal);
	if (err)
		goto err_free_attr_list;

	return 0;

err_free_attr_list:
	counter_device_attr_list_free(&group->attr_list);
	return err;
}