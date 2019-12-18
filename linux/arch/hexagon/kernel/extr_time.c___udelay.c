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

/* Variables and functions */
 unsigned long long __vmgettime () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long fudgefactor ; 
 unsigned long pcycle_freq_mhz ; 

void __udelay(unsigned long usecs)
{
	unsigned long long start = __vmgettime();
	unsigned long long finish = (pcycle_freq_mhz * usecs) - fudgefactor;

	while ((__vmgettime() - start) < finish)
		cpu_relax(); /*  not sure how this improves readability  */
}