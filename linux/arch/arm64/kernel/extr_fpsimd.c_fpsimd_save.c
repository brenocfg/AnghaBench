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
struct fpsimd_last_state_struct {scalar_t__ sve_vl; TYPE_1__* st; scalar_t__ sve_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  fpsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SI_KERNEL ; 
 int /*<<< orphan*/  TIF_FOREIGN_FPSTATE ; 
 int /*<<< orphan*/  TIF_SVE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  force_signal_inject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpsimd_last_state ; 
 int /*<<< orphan*/  fpsimd_save_state (TYPE_1__*) ; 
 int /*<<< orphan*/  have_cpu_fpsimd_context () ; 
 int sve_ffr_offset (scalar_t__) ; 
 scalar_t__ sve_get_vl () ; 
 int /*<<< orphan*/  sve_save_state (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ system_supports_sve () ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 struct fpsimd_last_state_struct* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fpsimd_save(void)
{
	struct fpsimd_last_state_struct const *last =
		this_cpu_ptr(&fpsimd_last_state);
	/* set by fpsimd_bind_task_to_cpu() or fpsimd_bind_state_to_cpu() */

	WARN_ON(!have_cpu_fpsimd_context());

	if (!test_thread_flag(TIF_FOREIGN_FPSTATE)) {
		if (system_supports_sve() && test_thread_flag(TIF_SVE)) {
			if (WARN_ON(sve_get_vl() != last->sve_vl)) {
				/*
				 * Can't save the user regs, so current would
				 * re-enter user with corrupt state.
				 * There's no way to recover, so kill it:
				 */
				force_signal_inject(SIGKILL, SI_KERNEL, 0);
				return;
			}

			sve_save_state((char *)last->sve_state +
						sve_ffr_offset(last->sve_vl),
				       &last->st->fpsr);
		} else
			fpsimd_save_state(last->st);
	}
}