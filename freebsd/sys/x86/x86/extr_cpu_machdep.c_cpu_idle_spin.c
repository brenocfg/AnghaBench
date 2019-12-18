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
typedef  int /*<<< orphan*/  sbintime_t ;
struct TYPE_2__ {int idle_state; } ;

/* Variables and functions */
 TYPE_1__* PCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_RUNNING ; 
 int /*<<< orphan*/  atomic_store_int (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int /*<<< orphan*/  monitorbuf ; 
 scalar_t__ sched_runnable () ; 

__attribute__((used)) static void
cpu_idle_spin(sbintime_t sbt)
{
	int *state;
	int i;

	state = &PCPU_PTR(monitorbuf)->idle_state;
	atomic_store_int(state, STATE_RUNNING);

	/*
	 * The sched_runnable() call is racy but as long as there is
	 * a loop missing it one time will have just a little impact if any 
	 * (and it is much better than missing the check at all).
	 */
	for (i = 0; i < 1000; i++) {
		if (sched_runnable())
			return;
		cpu_spinwait();
	}
}