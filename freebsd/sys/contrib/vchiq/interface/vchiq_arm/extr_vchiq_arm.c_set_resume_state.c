#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum vc_resume_status { ____Placeholder_vc_resume_status } vc_resume_status ;
struct TYPE_4__ {int vc_resume_state; int /*<<< orphan*/  vc_resume_complete; } ;
typedef  TYPE_1__ VCHIQ_ARM_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  INIT_COMPLETION (int /*<<< orphan*/ ) ; 
#define  VC_RESUME_FAILED 132 
#define  VC_RESUME_IDLE 131 
#define  VC_RESUME_IN_PROGRESS 130 
#define  VC_RESUME_REQUESTED 129 
#define  VC_RESUME_RESUMED 128 
 int /*<<< orphan*/  VC_SUSPEND_IDLE ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_suspend_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
set_resume_state(VCHIQ_ARM_STATE_T *arm_state,
	enum vc_resume_status new_state)
{
	/* set the state in all cases */
	arm_state->vc_resume_state = new_state;

	/* state specific additional actions */
	switch (new_state) {
	case VC_RESUME_FAILED:
		break;
	case VC_RESUME_IDLE:
		/* TODO: reinit_completion */
		INIT_COMPLETION(arm_state->vc_resume_complete);
		break;
	case VC_RESUME_REQUESTED:
		break;
	case VC_RESUME_IN_PROGRESS:
		break;
	case VC_RESUME_RESUMED:
		complete_all(&arm_state->vc_resume_complete);
		set_suspend_state(arm_state, VC_SUSPEND_IDLE);
		break;
	default:
		BUG();
		break;
	}
}