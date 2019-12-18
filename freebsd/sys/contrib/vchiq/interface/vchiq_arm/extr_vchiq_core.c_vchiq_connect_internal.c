#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_10__ {scalar_t__ conn_state; int /*<<< orphan*/  connect; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
struct TYPE_11__ {scalar_t__ srvstate; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;
typedef  int /*<<< orphan*/  VCHIQ_INSTANCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  QMFLAGS_IS_BLOCKING ; 
 scalar_t__ VCHIQ_CONNSTATE_CONNECTED ; 
 scalar_t__ VCHIQ_CONNSTATE_CONNECTING ; 
 scalar_t__ VCHIQ_CONNSTATE_DISCONNECTED ; 
 int /*<<< orphan*/  VCHIQ_MAKE_MSG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_MSG_CONNECT ; 
 scalar_t__ VCHIQ_RETRY ; 
 scalar_t__ VCHIQ_SRVSTATE_HIDDEN ; 
 int /*<<< orphan*/  VCHIQ_SRVSTATE_LISTENING ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 TYPE_2__* next_service_by_instance (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ queue_message (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_service (TYPE_2__*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_set_conn_state (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vchiq_set_service_state (TYPE_2__*,int /*<<< orphan*/ ) ; 

VCHIQ_STATUS_T
vchiq_connect_internal(VCHIQ_STATE_T *state, VCHIQ_INSTANCE_T instance)
{
	VCHIQ_SERVICE_T *service;
	int i;

	/* Find all services registered to this client and enable them. */
	i = 0;
	while ((service = next_service_by_instance(state, instance,
		&i)) !=	NULL) {
		if (service->srvstate == VCHIQ_SRVSTATE_HIDDEN)
			vchiq_set_service_state(service,
				VCHIQ_SRVSTATE_LISTENING);
		unlock_service(service);
	}

	if (state->conn_state == VCHIQ_CONNSTATE_DISCONNECTED) {
		if (queue_message(state, NULL,
			VCHIQ_MAKE_MSG(VCHIQ_MSG_CONNECT, 0, 0), NULL, 0,
			0, QMFLAGS_IS_BLOCKING) == VCHIQ_RETRY)
			return VCHIQ_RETRY;

		vchiq_set_conn_state(state, VCHIQ_CONNSTATE_CONNECTING);
	}

	if (state->conn_state == VCHIQ_CONNSTATE_CONNECTING) {
		if (down_interruptible(&state->connect) != 0)
			return VCHIQ_RETRY;

		vchiq_set_conn_state(state, VCHIQ_CONNSTATE_CONNECTED);
		up(&state->connect);
	}

	return VCHIQ_SUCCESS;
}