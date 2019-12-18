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
typedef  size_t u_int ;
struct monitorbuf {int /*<<< orphan*/  stop_state; } ;

/* Variables and functions */
 int CPUID2_MON ; 
 int /*<<< orphan*/  CPU_ISSET (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_BSP () ; 
 scalar_t__ MONITOR_STOPSTATE_STOPPED ; 
 int /*<<< orphan*/  MWAIT_C1 ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 struct monitorbuf* PCPU_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ atomic_load_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store_int (int /*<<< orphan*/ *,scalar_t__) ; 
 int cpu_feature2 ; 
 int /*<<< orphan*/  cpu_monitor (struct monitorbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_mwait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  cpustop_handler_post (size_t) ; 
 int /*<<< orphan*/  halt () ; 
 int /*<<< orphan*/  ia32_pause () ; 
 int /*<<< orphan*/  monitorbuf ; 
 int /*<<< orphan*/  mwait_cpustop_broken ; 
 int /*<<< orphan*/ * panicstr ; 
 int /*<<< orphan*/  savectx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  started_cpus ; 
 scalar_t__ stop_mwait ; 
 int /*<<< orphan*/ * stoppcbs ; 
 int /*<<< orphan*/  stopped_cpus ; 

void
cpustop_handler(void)
{
	struct monitorbuf *mb;
	u_int cpu;
	bool use_mwait;

	cpu = PCPU_GET(cpuid);

	savectx(&stoppcbs[cpu]);

	use_mwait = (stop_mwait && (cpu_feature2 & CPUID2_MON) != 0 &&
	    !mwait_cpustop_broken);
	if (use_mwait) {
		mb = PCPU_PTR(monitorbuf);
		atomic_store_int(&mb->stop_state,
		    MONITOR_STOPSTATE_STOPPED);
	}

	/* Indicate that we are stopped */
	CPU_SET_ATOMIC(cpu, &stopped_cpus);

	/* Wait for restart */
	while (!CPU_ISSET(cpu, &started_cpus)) {
		if (use_mwait) {
			cpu_monitor(mb, 0, 0);
			if (atomic_load_int(&mb->stop_state) ==
			    MONITOR_STOPSTATE_STOPPED)
				cpu_mwait(0, MWAIT_C1);
			continue;
		}

		ia32_pause();

		/*
		 * Halt non-BSP CPUs on panic -- we're never going to need them
		 * again, and might as well save power / release resources
		 * (e.g., overprovisioned VM infrastructure).
		 */
		while (__predict_false(!IS_BSP() && panicstr != NULL))
			halt();
	}

	cpustop_handler_post(cpu);
}