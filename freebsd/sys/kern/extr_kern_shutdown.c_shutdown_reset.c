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
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  cpu_reset () ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  smp_ipi_mtx ; 
 int /*<<< orphan*/  spinlock_enter () ; 

__attribute__((used)) static void
shutdown_reset(void *junk, int howto)
{

	printf("Rebooting...\n");
	DELAY(1000000);	/* wait 1 sec for printf's to complete and be read */

	/*
	 * Acquiring smp_ipi_mtx here has a double effect:
	 * - it disables interrupts avoiding CPU0 preemption
	 *   by fast handlers (thus deadlocking  against other CPUs)
	 * - it avoids deadlocks against smp_rendezvous() or, more 
	 *   generally, threads busy-waiting, with this spinlock held,
	 *   and waiting for responses by threads on other CPUs
	 *   (ie. smp_tlb_shootdown()).
	 *
	 * For the !SMP case it just needs to handle the former problem.
	 */
#ifdef SMP
	mtx_lock_spin(&smp_ipi_mtx);
#else
	spinlock_enter();
#endif

	/* cpu_boot(howto); */ /* doesn't do anything at the moment */
	cpu_reset();
	/* NOTREACHED */ /* assuming reset worked */
}