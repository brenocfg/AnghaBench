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
typedef  size_t ssize_t ;
struct TYPE_2__ {unsigned long attr_freeze_on_smi; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  flip_smm_bit ; 
 int /*<<< orphan*/  freeze_on_smi_mutex ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 size_t kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,unsigned long*,int) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static ssize_t freeze_on_smi_store(struct device *cdev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	unsigned long val;
	ssize_t ret;

	ret = kstrtoul(buf, 0, &val);
	if (ret)
		return ret;

	if (val > 1)
		return -EINVAL;

	mutex_lock(&freeze_on_smi_mutex);

	if (x86_pmu.attr_freeze_on_smi == val)
		goto done;

	x86_pmu.attr_freeze_on_smi = val;

	get_online_cpus();
	on_each_cpu(flip_smm_bit, &val, 1);
	put_online_cpus();
done:
	mutex_unlock(&freeze_on_smi_mutex);

	return count;
}