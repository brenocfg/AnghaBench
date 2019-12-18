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
struct notifier_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  udelay_val; } ;

/* Variables and functions */
 unsigned long CPUFREQ_POSTCHANGE ; 
 int NOTIFY_OK ; 
 TYPE_1__ current_cpu_data ; 
 int /*<<< orphan*/  loops_per_jiffy ; 

__attribute__((used)) static int ls1x_cpufreq_notifier(struct notifier_block *nb,
				 unsigned long val, void *data)
{
	if (val == CPUFREQ_POSTCHANGE)
		current_cpu_data.udelay_val = loops_per_jiffy;

	return NOTIFY_OK;
}