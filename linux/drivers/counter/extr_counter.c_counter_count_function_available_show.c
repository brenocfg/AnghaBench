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
struct counter_func_avail_unit {int* functions_list; size_t num_functions; } ;
struct counter_device_attr {struct counter_func_avail_unit* component; } ;
typedef  int ssize_t ;
typedef  enum counter_count_function { ____Placeholder_counter_count_function } counter_count_function ;

/* Variables and functions */
 char** counter_count_function_str ; 
 int sprintf (char*,char*,char*) ; 
 struct counter_device_attr* to_counter_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t counter_count_function_available_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	const struct counter_device_attr *const devattr = to_counter_attr(attr);
	const struct counter_func_avail_unit *const component = devattr->component;
	const enum counter_count_function *const func_list = component->functions_list;
	const size_t num_functions = component->num_functions;
	size_t i;
	enum counter_count_function function;
	ssize_t len = 0;

	for (i = 0; i < num_functions; i++) {
		function = func_list[i];
		len += sprintf(buf + len, "%s\n",
			       counter_count_function_str[function]);
	}

	return len;
}