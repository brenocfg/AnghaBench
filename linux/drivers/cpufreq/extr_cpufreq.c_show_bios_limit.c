#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int max_freq; } ;
struct cpufreq_policy {TYPE_1__ cpuinfo; int /*<<< orphan*/  cpu; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int (* bios_limit ) (int /*<<< orphan*/ ,unsigned int*) ;} ;

/* Variables and functions */
 TYPE_2__* cpufreq_driver ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static ssize_t show_bios_limit(struct cpufreq_policy *policy, char *buf)
{
	unsigned int limit;
	int ret;
	ret = cpufreq_driver->bios_limit(policy->cpu, &limit);
	if (!ret)
		return sprintf(buf, "%u\n", limit);
	return sprintf(buf, "%u\n", policy->cpuinfo.max_freq);
}