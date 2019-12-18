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
typedef  int ssize_t ;

/* Variables and functions */
 int hwp_boost ; 
 int /*<<< orphan*/  intel_pstate_driver_lock ; 
 int /*<<< orphan*/  intel_pstate_update_policies () ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t store_hwp_dynamic_boost(struct kobject *a,
				       struct kobj_attribute *b,
				       const char *buf, size_t count)
{
	unsigned int input;
	int ret;

	ret = kstrtouint(buf, 10, &input);
	if (ret)
		return ret;

	mutex_lock(&intel_pstate_driver_lock);
	hwp_boost = !!input;
	intel_pstate_update_policies();
	mutex_unlock(&intel_pstate_driver_lock);

	return count;
}