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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OMAP_32K_TIMER ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned short enable_dyn_sleep ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int sscanf (char const*,char*,unsigned short*) ; 

__attribute__((used)) static ssize_t idle_store(struct kobject *kobj, struct kobj_attribute *attr,
			  const char * buf, size_t n)
{
	unsigned short value;
	if (sscanf(buf, "%hu", &value) != 1 ||
	    (value != 0 && value != 1) ||
	    (value != 0 && !IS_ENABLED(CONFIG_OMAP_32K_TIMER))) {
		pr_err("idle_sleep_store: Invalid value\n");
		return -EINVAL;
	}
	enable_dyn_sleep = value;
	return n;
}