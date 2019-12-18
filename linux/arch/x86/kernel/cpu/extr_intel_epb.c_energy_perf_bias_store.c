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
typedef  int u64 ;
struct device_attribute {int dummy; } ;
struct device {unsigned int id; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EPB_MASK ; 
 int MAX_EPB ; 
 int /*<<< orphan*/  MSR_IA32_ENERGY_PERF_BIAS ; 
 int __sysfs_match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int* energ_perf_values ; 
 int /*<<< orphan*/  energy_perf_strings ; 
 scalar_t__ kstrtou64 (char const*,int /*<<< orphan*/ ,int*) ; 
 int rdmsrl_on_cpu (unsigned int,int /*<<< orphan*/ ,int*) ; 
 int wrmsrl_on_cpu (unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t energy_perf_bias_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	unsigned int cpu = dev->id;
	u64 epb, val;
	int ret;

	ret = __sysfs_match_string(energy_perf_strings,
				   ARRAY_SIZE(energy_perf_strings), buf);
	if (ret >= 0)
		val = energ_perf_values[ret];
	else if (kstrtou64(buf, 0, &val) || val > MAX_EPB)
		return -EINVAL;

	ret = rdmsrl_on_cpu(cpu, MSR_IA32_ENERGY_PERF_BIAS, &epb);
	if (ret < 0)
		return ret;

	ret = wrmsrl_on_cpu(cpu, MSR_IA32_ENERGY_PERF_BIAS,
			    (epb & ~EPB_MASK) | val);
	if (ret < 0)
		return ret;

	return count;
}