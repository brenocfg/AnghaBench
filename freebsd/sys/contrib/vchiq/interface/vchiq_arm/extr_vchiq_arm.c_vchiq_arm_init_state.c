#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_STATE_T ;
struct TYPE_6__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct TYPE_5__ {scalar_t__ first_connect; TYPE_4__ suspend_timer; scalar_t__ suspend_timer_running; int /*<<< orphan*/  suspend_timer_timeout; int /*<<< orphan*/  blocked_blocker; int /*<<< orphan*/  resume_blocker; int /*<<< orphan*/  vc_resume_complete; int /*<<< orphan*/  vc_suspend_complete; int /*<<< orphan*/  ka_release_count; int /*<<< orphan*/  ka_use_ack_count; int /*<<< orphan*/  ka_use_count; int /*<<< orphan*/  ka_evt; int /*<<< orphan*/  susp_res_lock; } ;
typedef  TYPE_1__ VCHIQ_ARM_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SUSPEND_TIMER_TIMEOUT_MS ; 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  VC_RESUME_RESUMED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (TYPE_4__*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_resume_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suspend_timer_callback ; 

VCHIQ_STATUS_T
vchiq_arm_init_state(VCHIQ_STATE_T *state, VCHIQ_ARM_STATE_T *arm_state)
{
	VCHIQ_STATUS_T status = VCHIQ_SUCCESS;

	if (arm_state) {
		rwlock_init(&arm_state->susp_res_lock);

		init_completion(&arm_state->ka_evt);
		atomic_set(&arm_state->ka_use_count, 0);
		atomic_set(&arm_state->ka_use_ack_count, 0);
		atomic_set(&arm_state->ka_release_count, 0);

		init_completion(&arm_state->vc_suspend_complete);

		init_completion(&arm_state->vc_resume_complete);
		/* Initialise to 'done' state.  We only want to block on resume
		 * completion while videocore is suspended. */
		set_resume_state(arm_state, VC_RESUME_RESUMED);

		init_completion(&arm_state->resume_blocker);
		/* Initialise to 'done' state.  We only want to block on this
		 * completion while resume is blocked */
		complete_all(&arm_state->resume_blocker);

		init_completion(&arm_state->blocked_blocker);
		/* Initialise to 'done' state.  We only want to block on this
		 * completion while things are waiting on the resume blocker */
		complete_all(&arm_state->blocked_blocker);

		arm_state->suspend_timer_timeout = SUSPEND_TIMER_TIMEOUT_MS;
		arm_state->suspend_timer_running = 0;
		init_timer(&arm_state->suspend_timer);
		arm_state->suspend_timer.data = (unsigned long)(state);
		arm_state->suspend_timer.function = suspend_timer_callback;

		arm_state->first_connect = 0;

	}
	return status;
}