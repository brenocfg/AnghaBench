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
#define  ARM64_SSBD_FORCE_DISABLE 131 
#define  ARM64_SSBD_FORCE_ENABLE 130 
#define  ARM64_SSBD_KERNEL 129 
#define  ARM64_SSBD_UNKNOWN 128 
 int EINVAL ; 
 int PR_SPEC_DISABLE ; 
 int PR_SPEC_ENABLE ; 
 int PR_SPEC_FORCE_DISABLE ; 
 int PR_SPEC_NOT_AFFECTED ; 
 int PR_SPEC_PRCTL ; 
 int arm64_get_ssbd_state () ; 
 int /*<<< orphan*/  task_spec_ssb_disable (struct task_struct*) ; 
 int /*<<< orphan*/  task_spec_ssb_force_disable (struct task_struct*) ; 

__attribute__((used)) static int ssbd_prctl_get(struct task_struct *task)
{
	switch (arm64_get_ssbd_state()) {
	case ARM64_SSBD_UNKNOWN:
		return -EINVAL;
	case ARM64_SSBD_FORCE_ENABLE:
		return PR_SPEC_DISABLE;
	case ARM64_SSBD_KERNEL:
		if (task_spec_ssb_force_disable(task))
			return PR_SPEC_PRCTL | PR_SPEC_FORCE_DISABLE;
		if (task_spec_ssb_disable(task))
			return PR_SPEC_PRCTL | PR_SPEC_DISABLE;
		return PR_SPEC_PRCTL | PR_SPEC_ENABLE;
	case ARM64_SSBD_FORCE_DISABLE:
		return PR_SPEC_ENABLE;
	default:
		return PR_SPEC_NOT_AFFECTED;
	}
}