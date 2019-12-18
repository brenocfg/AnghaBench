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
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct dev_ext_attribute* to_ext_attr (struct device_attribute*) ; 

ssize_t device_store_ulong(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t size)
{
	struct dev_ext_attribute *ea = to_ext_attr(attr);
	int ret;
	unsigned long new;

	ret = kstrtoul(buf, 0, &new);
	if (ret)
		return ret;
	*(unsigned long *)(ea->var) = new;
	/* Always return full write size even if we didn't consume all */
	return size;
}