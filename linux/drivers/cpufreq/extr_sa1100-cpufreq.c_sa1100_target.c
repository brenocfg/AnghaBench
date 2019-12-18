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
struct cpufreq_policy {int dummy; } ;
struct TYPE_2__ {unsigned int frequency; } ;

/* Variables and functions */
 unsigned int PPCR ; 
 int /*<<< orphan*/  sa1100_update_dram_timings (unsigned int,unsigned int) ; 
 TYPE_1__* sa11x0_freq_table ; 
 unsigned int sa11x0_getspeed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sa1100_target(struct cpufreq_policy *policy, unsigned int ppcr)
{
	unsigned int cur = sa11x0_getspeed(0);
	unsigned int new_freq;

	new_freq = sa11x0_freq_table[ppcr].frequency;

	if (new_freq > cur)
		sa1100_update_dram_timings(cur, new_freq);

	PPCR = ppcr;

	if (new_freq < cur)
		sa1100_update_dram_timings(cur, new_freq);

	return 0;
}