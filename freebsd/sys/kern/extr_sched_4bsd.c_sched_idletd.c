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
struct pcpuidlestat {int idlecalls; int oldidlecalls; } ;

/* Variables and functions */
 struct pcpuidlestat* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int SWT_IDLE ; 
 int SW_VOL ; 
 int /*<<< orphan*/  THREAD_NO_SLEEPING () ; 
 int /*<<< orphan*/  cpu_idle (int) ; 
 int /*<<< orphan*/  idlestat ; 
 int /*<<< orphan*/  mi_switch (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_lock ; 
 scalar_t__ sched_runnable () ; 

void
sched_idletd(void *dummy)
{
	struct pcpuidlestat *stat;

	THREAD_NO_SLEEPING();
	stat = DPCPU_PTR(idlestat);
	for (;;) {
		mtx_assert(&Giant, MA_NOTOWNED);

		while (sched_runnable() == 0) {
			cpu_idle(stat->idlecalls + stat->oldidlecalls > 64);
			stat->idlecalls++;
		}

		mtx_lock_spin(&sched_lock);
		mi_switch(SW_VOL | SWT_IDLE, NULL);
		mtx_unlock_spin(&sched_lock);
	}
}