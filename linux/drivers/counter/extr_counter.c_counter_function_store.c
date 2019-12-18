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
struct counter_device_attr {struct counter_count_unit* component; } ;
struct counter_device {TYPE_1__* ops; } ;
struct counter_count_unit {struct counter_count* count; } ;
struct counter_count {size_t num_functions; int* functions_list; size_t function; } ;
typedef  int ssize_t ;
typedef  enum counter_count_function { ____Placeholder_counter_count_function } counter_count_function ;
struct TYPE_2__ {int (* function_set ) (struct counter_device* const,struct counter_count* const,size_t) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * counter_count_function_str ; 
 struct counter_device* dev_get_drvdata (struct device*) ; 
 int stub1 (struct counter_device* const,struct counter_count* const,size_t) ; 
 scalar_t__ sysfs_streq (char const*,int /*<<< orphan*/ ) ; 
 struct counter_device_attr* to_counter_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t counter_function_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t len)
{
	const struct counter_device_attr *const devattr = to_counter_attr(attr);
	const struct counter_count_unit *const component = devattr->component;
	struct counter_count *const count = component->count;
	const size_t num_functions = count->num_functions;
	size_t func_index;
	enum counter_count_function function;
	int err;
	struct counter_device *const counter = dev_get_drvdata(dev);

	/* Find requested Count function mode */
	for (func_index = 0; func_index < num_functions; func_index++) {
		function = count->functions_list[func_index];
		if (sysfs_streq(buf, counter_count_function_str[function]))
			break;
	}
	/* Return error if requested Count function mode not found */
	if (func_index >= num_functions)
		return -EINVAL;

	err = counter->ops->function_set(counter, count, func_index);
	if (err)
		return err;

	count->function = func_index;

	return len;
}