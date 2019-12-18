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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct counter_synapse {size_t num_actions; int* actions_list; size_t action; } ;
struct counter_device_attr {struct counter_action_unit* component; } ;
struct counter_device {TYPE_1__* ops; } ;
struct counter_count {int dummy; } ;
struct counter_action_unit {struct counter_count* count; struct counter_synapse* synapse; } ;
typedef  int ssize_t ;
typedef  enum counter_synapse_action { ____Placeholder_counter_synapse_action } counter_synapse_action ;
struct TYPE_2__ {int (* action_set ) (struct counter_device* const,struct counter_count* const,struct counter_synapse* const,size_t) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * counter_synapse_action_str ; 
 struct counter_device* dev_get_drvdata (struct device*) ; 
 int stub1 (struct counter_device* const,struct counter_count* const,struct counter_synapse* const,size_t) ; 
 scalar_t__ sysfs_streq (char const*,int /*<<< orphan*/ ) ; 
 struct counter_device_attr* to_counter_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t counter_action_store(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t len)
{
	const struct counter_device_attr *const devattr = to_counter_attr(attr);
	const struct counter_action_unit *const component = devattr->component;
	struct counter_synapse *const synapse = component->synapse;
	size_t action_index;
	const size_t num_actions = synapse->num_actions;
	enum counter_synapse_action action;
	int err;
	struct counter_device *const counter = dev_get_drvdata(dev);
	struct counter_count *const count = component->count;

	/* Find requested action mode */
	for (action_index = 0; action_index < num_actions; action_index++) {
		action = synapse->actions_list[action_index];
		if (sysfs_streq(buf, counter_synapse_action_str[action]))
			break;
	}
	/* If requested action mode not found */
	if (action_index >= num_actions)
		return -EINVAL;

	err = counter->ops->action_set(counter, count, synapse, action_index);
	if (err)
		return err;

	synapse->action = action_index;

	return len;
}