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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct counter_device_attr {struct counter_action_avail_unit* component; } ;
struct counter_action_avail_unit {size_t num_actions; int* actions_list; } ;
typedef  int ssize_t ;
typedef  enum counter_synapse_action { ____Placeholder_counter_synapse_action } counter_synapse_action ;

/* Variables and functions */
 char** counter_synapse_action_str ; 
 int sprintf (char*,char*,char*) ; 
 struct counter_device_attr* to_counter_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t counter_synapse_action_available_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	const struct counter_device_attr *const devattr = to_counter_attr(attr);
	const struct counter_action_avail_unit *const component = devattr->component;
	size_t i;
	enum counter_synapse_action action;
	ssize_t len = 0;

	for (i = 0; i < component->num_actions; i++) {
		action = component->actions_list[i];
		len += sprintf(buf + len, "%s\n",
			       counter_synapse_action_str[action]);
	}

	return len;
}