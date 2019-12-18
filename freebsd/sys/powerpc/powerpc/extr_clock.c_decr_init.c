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
struct cpuref {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int curcpu ; 
 int /*<<< orphan*/ * decr_counts ; 
 int /*<<< orphan*/  decr_et_stop (int /*<<< orphan*/ *) ; 
 int initialized ; 
 int /*<<< orphan*/  intrcnt_add (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mftb ; 
 int /*<<< orphan*/  platform_smp_first_cpu (struct cpuref*) ; 
 scalar_t__ platform_smp_get_bsp (struct cpuref*) ; 
 int platform_timebase_freq (struct cpuref*) ; 
 int ps_per_tick ; 
 int /*<<< orphan*/  set_cputicker (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int ticks_per_sec ; 

void
decr_init(void)
{
	struct cpuref cpu;
	char buf[32];

	/*
	 * Check the BSP's timebase frequency. Sometimes we can't find the BSP,
	 * so fall back to the first CPU in this case.
	 */
	if (platform_smp_get_bsp(&cpu) != 0)
		platform_smp_first_cpu(&cpu);
	ticks_per_sec = platform_timebase_freq(&cpu);
	ps_per_tick = 1000000000000 / ticks_per_sec;

	set_cputicker(mftb, ticks_per_sec, 0);
	snprintf(buf, sizeof(buf), "cpu%d:decrementer", curcpu);
	intrcnt_add(buf, &decr_counts[curcpu]);
	decr_et_stop(NULL);
	initialized = 1;
}