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
typedef  int /*<<< orphan*/  u64 ;
struct device_attribute {int dummy; } ;
struct device {unsigned int id; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_ENERGY_PERF_BIAS ; 
 int rdmsrl_on_cpu (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t energy_perf_bias_show(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	unsigned int cpu = dev->id;
	u64 epb;
	int ret;

	ret = rdmsrl_on_cpu(cpu, MSR_IA32_ENERGY_PERF_BIAS, &epb);
	if (ret < 0)
		return ret;

	return sprintf(buf, "%llu\n", epb);
}