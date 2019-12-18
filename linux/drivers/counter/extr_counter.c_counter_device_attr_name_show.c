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
struct counter_name_unit {char* name; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct counter_name_unit* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 TYPE_1__* to_counter_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t counter_device_attr_name_show(struct device *dev,
					     struct device_attribute *attr,
					     char *buf)
{
	const struct counter_name_unit *const comp = to_counter_attr(attr)->component;

	return sprintf(buf, "%s\n", comp->name);
}