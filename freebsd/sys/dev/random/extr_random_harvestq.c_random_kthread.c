#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_5__ {scalar_t__* buf; } ;
struct TYPE_4__ {int out; int in; scalar_t__ ring; } ;
struct TYPE_6__ {int /*<<< orphan*/  hc_kthread_proc; TYPE_2__ hc_entropy_fast_accumulator; TYPE_1__ hc_entropy_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_PREL (int) ; 
 size_t RANDOM_ACCUM_MAX ; 
 int RANDOM_RING_MAX ; 
 int /*<<< orphan*/  RANDOM_UMA ; 
 int SBT_1S ; 
 TYPE_3__ harvest_context ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_harvest_direct (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_harvestq_fast_process_event (scalar_t__) ; 
 int random_kthread_control ; 
 int /*<<< orphan*/  random_sources_feed () ; 
 int /*<<< orphan*/  tsleep_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
random_kthread(void)
{
        u_int maxloop, ring_out, i;

	/*
	 * Locking is not needed as this is the only place we modify ring.out, and
	 * we only examine ring.in without changing it. Both of these are volatile,
	 * and this is a unique thread.
	 */
	for (random_kthread_control = 1; random_kthread_control;) {
		/* Deal with events, if any. Restrict the number we do in one go. */
		maxloop = RANDOM_RING_MAX;
		while (harvest_context.hc_entropy_ring.out != harvest_context.hc_entropy_ring.in) {
			ring_out = (harvest_context.hc_entropy_ring.out + 1)%RANDOM_RING_MAX;
			random_harvestq_fast_process_event(harvest_context.hc_entropy_ring.ring + ring_out);
			harvest_context.hc_entropy_ring.out = ring_out;
			if (!--maxloop)
				break;
		}
		random_sources_feed();
		/* XXX: FIX!! Increase the high-performance data rate? Need some measurements first. */
		for (i = 0; i < RANDOM_ACCUM_MAX; i++) {
			if (harvest_context.hc_entropy_fast_accumulator.buf[i]) {
				random_harvest_direct(harvest_context.hc_entropy_fast_accumulator.buf + i, sizeof(harvest_context.hc_entropy_fast_accumulator.buf[0]), RANDOM_UMA);
				harvest_context.hc_entropy_fast_accumulator.buf[i] = 0;
			}
		}
		/* XXX: FIX!! This is a *great* place to pass hardware/live entropy to random(9) */
		tsleep_sbt(&harvest_context.hc_kthread_proc, 0, "-", SBT_1S/10, 0, C_PREL(1));
	}
	random_kthread_control = -1;
	wakeup(&harvest_context.hc_kthread_proc);
	kproc_exit(0);
	/* NOTREACHED */
}