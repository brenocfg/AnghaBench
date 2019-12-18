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
 int /*<<< orphan*/  COUNTON ; 
 int NR_LOOPS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_count_start ; 
 int /*<<< orphan*/  count_count_stop ; 
 int /*<<< orphan*/  get_cycles () ; 
 int /*<<< orphan*/  initcount ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  openrisc_timer_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openrisc_timer_set_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 

void synchronise_count_master(int cpu)
{
	int i;
	unsigned long flags;

	pr_info("Synchronize counters for CPU %u: ", cpu);

	local_irq_save(flags);

	/*
	 * We loop a few times to get a primed instruction cache,
	 * then the last pass is more or less synchronised and
	 * the master and slaves each set their cycle counters to a known
	 * value all at once. This reduces the chance of having random offsets
	 * between the processors, and guarantees that the maximum
	 * delay between the cycle counters is never bigger than
	 * the latency of information-passing (cachelines) between
	 * two CPUs.
	 */

	for (i = 0; i < NR_LOOPS; i++) {
		/* slaves loop on '!= 2' */
		while (atomic_read(&count_count_start) != 1)
			mb();
		atomic_set(&count_count_stop, 0);
		smp_wmb();

		/* Let the slave writes its count register */
		atomic_inc(&count_count_start);

		/* Count will be initialised to current timer */
		if (i == 1)
			initcount = get_cycles();

		/*
		 * Everyone initialises count in the last loop:
		 */
		if (i == NR_LOOPS-1)
			openrisc_timer_set(initcount);

		/*
		 * Wait for slave to leave the synchronization point:
		 */
		while (atomic_read(&count_count_stop) != 1)
			mb();
		atomic_set(&count_count_start, 0);
		smp_wmb();
		atomic_inc(&count_count_stop);
	}
	/* Arrange for an interrupt in a short while */
	openrisc_timer_set_next(COUNTON);

	local_irq_restore(flags);

	/*
	 * i386 code reported the skew here, but the
	 * count registers were almost certainly out of sync
	 * so no point in alarming people
	 */
	pr_cont("done.\n");
}