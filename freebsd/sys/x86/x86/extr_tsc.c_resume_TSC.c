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
struct TYPE_2__ {int tc_quality; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int) ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  smp_tsc_adjust ; 
 int test_tsc (int /*<<< orphan*/ ) ; 
 TYPE_1__ tsc_timecounter ; 

void
resume_TSC(void)
{
#ifdef SMP
	int quality;

	/* If TSC was not good on boot, it is unlikely to become good now. */
	if (tsc_timecounter.tc_quality < 0)
		return;
	/* Nothing to do with UP. */
	if (mp_ncpus < 2)
		return;

	/*
	 * If TSC was good, a single synchronization should be enough,
	 * but honour smp_tsc_adjust if it's set.
	 */
	quality = test_tsc(MAX(smp_tsc_adjust, 1));
	if (quality != tsc_timecounter.tc_quality) {
		printf("TSC timecounter quality changed: %d -> %d\n",
		    tsc_timecounter.tc_quality, quality);
		tsc_timecounter.tc_quality = quality;
	}
#endif /* SMP */
}