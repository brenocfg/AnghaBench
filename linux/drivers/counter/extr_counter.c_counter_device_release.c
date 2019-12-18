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
struct device {int dummy; } ;
struct counter_device_state {int /*<<< orphan*/  id; int /*<<< orphan*/  num_groups; int /*<<< orphan*/  groups_list; struct counter_device_state* const groups; } ;
struct counter_device {struct counter_device_state* device_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  counter_device_groups_list_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_ida ; 
 struct counter_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct counter_device_state* const) ; 

__attribute__((used)) static void counter_device_release(struct device *dev)
{
	struct counter_device *const counter = dev_get_drvdata(dev);
	struct counter_device_state *const device_state = counter->device_state;

	kfree(device_state->groups);
	counter_device_groups_list_free(device_state->groups_list,
					device_state->num_groups);
	ida_simple_remove(&counter_ida, device_state->id);
	kfree(device_state);
}