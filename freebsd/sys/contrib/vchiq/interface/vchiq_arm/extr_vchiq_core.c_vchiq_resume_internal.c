#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
struct TYPE_6__ {scalar_t__ conn_state; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_CONNSTATE_PAUSED ; 
 int /*<<< orphan*/  VCHIQ_CONNSTATE_RESUMING ; 
 int /*<<< orphan*/  VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_STATS_INC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  error_count ; 
 int /*<<< orphan*/  request_poll (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_set_conn_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

VCHIQ_STATUS_T
vchiq_resume_internal(VCHIQ_STATE_T *state)
{
	VCHIQ_STATUS_T status = VCHIQ_SUCCESS;

	if (state->conn_state == VCHIQ_CONNSTATE_PAUSED) {
		vchiq_set_conn_state(state, VCHIQ_CONNSTATE_RESUMING);
		request_poll(state, NULL, 0);
	} else {
		status = VCHIQ_ERROR;
		VCHIQ_STATS_INC(state, error_count);
	}

	return status;
}