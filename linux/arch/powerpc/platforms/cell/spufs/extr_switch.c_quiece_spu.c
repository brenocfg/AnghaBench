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
struct spu_state {int dummy; } ;
struct spu {int dummy; } ;

/* Variables and functions */
 scalar_t__ check_spu_isolate (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  disable_interrupts (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  do_mfc_mssync (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  halt_mfc_decr (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  handle_pending_interrupts (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  inhibit_user_access (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  issue_mfc_tlbie (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  remove_other_spu_access (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_mfc_cntl (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_mfc_sr1 (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_mfc_stopped_status (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_spu_runcntl (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_spu_status (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  save_timebase (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  set_switch_pending (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  set_watchdog_timer (struct spu_state*,struct spu*) ; 

__attribute__((used)) static int quiece_spu(struct spu_state *prev, struct spu *spu)
{
	/*
	 * Combined steps 2-18 of SPU context save sequence, which
	 * quiesce the SPU state (disable SPU execution, MFC command
	 * queues, decrementer, SPU interrupts, etc.).
	 *
	 * Returns      0 on success.
	 *              2 if failed step 2.
	 *              6 if failed step 6.
	 */

	if (check_spu_isolate(prev, spu)) {	/* Step 2. */
		return 2;
	}
	disable_interrupts(prev, spu);	        /* Step 3. */
	set_watchdog_timer(prev, spu);	        /* Step 4. */
	inhibit_user_access(prev, spu);	        /* Step 5. */
	if (check_spu_isolate(prev, spu)) {	/* Step 6. */
		return 6;
	}
	set_switch_pending(prev, spu);	        /* Step 7. */
	save_mfc_cntl(prev, spu);		/* Step 8. */
	save_spu_runcntl(prev, spu);	        /* Step 9. */
	save_mfc_sr1(prev, spu);	        /* Step 10. */
	save_spu_status(prev, spu);	        /* Step 11. */
	save_mfc_stopped_status(prev, spu);     /* Step 12. */
	halt_mfc_decr(prev, spu);	        /* Step 13. */
	save_timebase(prev, spu);		/* Step 14. */
	remove_other_spu_access(prev, spu);	/* Step 15. */
	do_mfc_mssync(prev, spu);	        /* Step 16. */
	issue_mfc_tlbie(prev, spu);	        /* Step 17. */
	handle_pending_interrupts(prev, spu);	/* Step 18. */

	return 0;
}