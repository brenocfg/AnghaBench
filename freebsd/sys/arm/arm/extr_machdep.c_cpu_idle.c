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
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_SPARE2 ; 
 int /*<<< orphan*/  cpu_activeclock () ; 
 int /*<<< orphan*/  cpu_idleclock () ; 
 int /*<<< orphan*/  cpu_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curcpu ; 
 int /*<<< orphan*/  sched_runnable () ; 
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  spinlock_exit () ; 

void
cpu_idle(int busy)
{

	CTR2(KTR_SPARE2, "cpu_idle(%d) at %d", busy, curcpu);
	spinlock_enter();
#ifndef NO_EVENTTIMERS
	if (!busy)
		cpu_idleclock();
#endif
	if (!sched_runnable())
		cpu_sleep(0);
#ifndef NO_EVENTTIMERS
	if (!busy)
		cpu_activeclock();
#endif
	spinlock_exit();
	CTR2(KTR_SPARE2, "cpu_idle(%d) at %d done", busy, curcpu);
}