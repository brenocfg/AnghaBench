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
struct dev_ext_attribute {scalar_t__ var; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct dev_ext_attribute* to_ext_attr (struct device_attribute*) ; 

ssize_t device_show_int(struct device *dev,
			struct device_attribute *attr,
			char *buf)
{
	struct dev_ext_attribute *ea = to_ext_attr(attr);

	return snprintf(buf, PAGE_SIZE, "%d\n", *(int *)(ea->var));
}