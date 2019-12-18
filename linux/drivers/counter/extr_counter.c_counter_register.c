#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  of_node; TYPE_1__* parent; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * type; } ;
struct counter_device_state {int id; int /*<<< orphan*/  num_groups; int /*<<< orphan*/  groups_list; struct counter_device_state* groups; TYPE_2__ dev; } ;
struct counter_device {TYPE_1__* parent; struct counter_device_state* device_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  counter_bus_type ; 
 int /*<<< orphan*/  counter_device_groups_list_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int counter_device_groups_list_prepare (struct counter_device* const) ; 
 int counter_device_groups_prepare (struct counter_device_state*) ; 
 int /*<<< orphan*/  counter_device_type ; 
 int /*<<< orphan*/  counter_ida ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct counter_device* const) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct counter_device_state*) ; 
 struct counter_device_state* kzalloc (int,int /*<<< orphan*/ ) ; 

int counter_register(struct counter_device *const counter)
{
	struct counter_device_state *device_state;
	int err;

	/* Allocate internal state container for Counter device */
	device_state = kzalloc(sizeof(*device_state), GFP_KERNEL);
	if (!device_state)
		return -ENOMEM;
	counter->device_state = device_state;

	/* Acquire unique ID */
	device_state->id = ida_simple_get(&counter_ida, 0, 0, GFP_KERNEL);
	if (device_state->id < 0) {
		err = device_state->id;
		goto err_free_device_state;
	}

	/* Configure device structure for Counter */
	device_state->dev.type = &counter_device_type;
	device_state->dev.bus = &counter_bus_type;
	if (counter->parent) {
		device_state->dev.parent = counter->parent;
		device_state->dev.of_node = counter->parent->of_node;
	}
	dev_set_name(&device_state->dev, "counter%d", device_state->id);
	device_initialize(&device_state->dev);
	dev_set_drvdata(&device_state->dev, counter);

	/* Prepare device attributes */
	err = counter_device_groups_list_prepare(counter);
	if (err)
		goto err_free_id;

	/* Organize device attributes to groups and match to device */
	err = counter_device_groups_prepare(device_state);
	if (err)
		goto err_free_groups_list;

	/* Add device to system */
	err = device_add(&device_state->dev);
	if (err)
		goto err_free_groups;

	return 0;

err_free_groups:
	kfree(device_state->groups);
err_free_groups_list:
	counter_device_groups_list_free(device_state->groups_list,
					device_state->num_groups);
err_free_id:
	ida_simple_remove(&counter_ida, device_state->id);
err_free_device_state:
	kfree(device_state);
	return err;
}