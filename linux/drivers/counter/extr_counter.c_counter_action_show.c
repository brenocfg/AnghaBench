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
struct counter_synapse {size_t action; int* actions_list; } ;
struct counter_device_attr {struct counter_action_unit* component; } ;
struct counter_device {TYPE_1__* ops; } ;
struct counter_count {int dummy; } ;
struct counter_action_unit {struct counter_synapse* synapse; struct counter_count* count; } ;
typedef  int ssize_t ;
typedef  enum counter_synapse_action { ____Placeholder_counter_synapse_action } counter_synapse_action ;
struct TYPE_2__ {int (* action_get ) (struct counter_device* const,struct counter_count* const,struct counter_synapse* const,size_t*) ;} ;

/* Variables and functions */
 char** counter_synapse_action_str ; 
 struct counter_device* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,char*) ; 
 int stub1 (struct counter_device* const,struct counter_count* const,struct counter_synapse* const,size_t*) ; 
 struct counter_device_attr* to_counter_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t counter_action_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	const struct counter_device_attr *const devattr = to_counter_attr(attr);
	int err;
	struct counter_device *const counter = dev_get_drvdata(dev);
	const struct counter_action_unit *const component = devattr->component;
	struct counter_count *const count = component->count;
	struct counter_synapse *const synapse = component->synapse;
	size_t action_index;
	enum counter_synapse_action action;

	err = counter->ops->action_get(counter, count, synapse, &action_index);
	if (err)
		return err;

	synapse->action = action_index;

	action = synapse->actions_list[action_index];
	return sprintf(buf, "%s\n", counter_synapse_action_str[action]);
}