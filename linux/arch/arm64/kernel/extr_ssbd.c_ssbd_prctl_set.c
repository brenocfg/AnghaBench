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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int ARM64_SSBD_FORCE_DISABLE ; 
 int ARM64_SSBD_FORCE_ENABLE ; 
 int ARM64_SSBD_MITIGATED ; 
 int ARM64_SSBD_UNKNOWN ; 
 int EINVAL ; 
 int EPERM ; 
 int ERANGE ; 
#define  PR_SPEC_DISABLE 130 
#define  PR_SPEC_ENABLE 129 
#define  PR_SPEC_FORCE_DISABLE 128 
 int /*<<< orphan*/  TIF_SSBD ; 
 int arm64_get_ssbd_state () ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssbd_ssbs_disable (struct task_struct*) ; 
 int /*<<< orphan*/  ssbd_ssbs_enable (struct task_struct*) ; 
 int /*<<< orphan*/  task_clear_spec_ssb_disable (struct task_struct*) ; 
 int /*<<< orphan*/  task_set_spec_ssb_disable (struct task_struct*) ; 
 int /*<<< orphan*/  task_set_spec_ssb_force_disable (struct task_struct*) ; 
 int /*<<< orphan*/  task_spec_ssb_force_disable (struct task_struct*) ; 

__attribute__((used)) static int ssbd_prctl_set(struct task_struct *task, unsigned long ctrl)
{
	int state = arm64_get_ssbd_state();

	/* Unsupported */
	if (state == ARM64_SSBD_UNKNOWN)
		return -EINVAL;

	/* Treat the unaffected/mitigated state separately */
	if (state == ARM64_SSBD_MITIGATED) {
		switch (ctrl) {
		case PR_SPEC_ENABLE:
			return -EPERM;
		case PR_SPEC_DISABLE:
		case PR_SPEC_FORCE_DISABLE:
			return 0;
		}
	}

	/*
	 * Things are a bit backward here: the arm64 internal API
	 * *enables the mitigation* when the userspace API *disables
	 * speculation*. So much fun.
	 */
	switch (ctrl) {
	case PR_SPEC_ENABLE:
		/* If speculation is force disabled, enable is not allowed */
		if (state == ARM64_SSBD_FORCE_ENABLE ||
		    task_spec_ssb_force_disable(task))
			return -EPERM;
		task_clear_spec_ssb_disable(task);
		clear_tsk_thread_flag(task, TIF_SSBD);
		ssbd_ssbs_enable(task);
		break;
	case PR_SPEC_DISABLE:
		if (state == ARM64_SSBD_FORCE_DISABLE)
			return -EPERM;
		task_set_spec_ssb_disable(task);
		set_tsk_thread_flag(task, TIF_SSBD);
		ssbd_ssbs_disable(task);
		break;
	case PR_SPEC_FORCE_DISABLE:
		if (state == ARM64_SSBD_FORCE_DISABLE)
			return -EPERM;
		task_set_spec_ssb_disable(task);
		task_set_spec_ssb_force_disable(task);
		set_tsk_thread_flag(task, TIF_SSBD);
		ssbd_ssbs_disable(task);
		break;
	default:
		return -ERANGE;
	}

	return 0;
}