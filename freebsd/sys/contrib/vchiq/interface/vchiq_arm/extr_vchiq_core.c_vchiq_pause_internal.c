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
struct TYPE_6__ {int conn_state; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;

/* Variables and functions */
#define  VCHIQ_CONNSTATE_CONNECTED 128 
 int /*<<< orphan*/  VCHIQ_CONNSTATE_PAUSING ; 
 int /*<<< orphan*/  VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_STATS_INC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 int /*<<< orphan*/ * conn_state_names ; 
 int /*<<< orphan*/  error_count ; 
 int /*<<< orphan*/  request_poll (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_set_conn_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

VCHIQ_STATUS_T
vchiq_pause_internal(VCHIQ_STATE_T *state)
{
	VCHIQ_STATUS_T status = VCHIQ_SUCCESS;

	switch (state->conn_state) {
	case VCHIQ_CONNSTATE_CONNECTED:
		/* Request a pause */
		vchiq_set_conn_state(state, VCHIQ_CONNSTATE_PAUSING);
		request_poll(state, NULL, 0);
		break;
	default:
		vchiq_log_error(vchiq_core_log_level,
			"vchiq_pause_internal in state %s\n",
			conn_state_names[state->conn_state]);
		status = VCHIQ_ERROR;
		VCHIQ_STATS_INC(state, error_count);
		break;
	}

	return status;
}