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
struct TYPE_2__ {int /*<<< orphan*/  set_boost; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpufreq_boost_set_sw ; 
 scalar_t__ cpufreq_boost_supported () ; 
 TYPE_1__* cpufreq_driver ; 
 int create_boost_sysfs_file () ; 

int cpufreq_enable_boost_support(void)
{
	if (!cpufreq_driver)
		return -EINVAL;

	if (cpufreq_boost_supported())
		return 0;

	cpufreq_driver->set_boost = cpufreq_boost_set_sw;

	/* This will get removed on driver unregister */
	return create_boost_sysfs_file();
}