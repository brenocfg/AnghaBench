#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ conn_state; TYPE_3__* service_quotas; int /*<<< orphan*/  slot_mutex; int /*<<< orphan*/  recycle_mutex; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
struct TYPE_6__ {int closing; size_t localport; TYPE_1__* state; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;
struct TYPE_7__ {int /*<<< orphan*/  quota_event; } ;
typedef  TYPE_3__ VCHIQ_SERVICE_QUOTA_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_CONNSTATE_PAUSE_SENT ; 
 int /*<<< orphan*/  lmutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lmutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mark_service_closing_internal(VCHIQ_SERVICE_T *service, int sh_thread)
{
	VCHIQ_STATE_T *state = service->state;
	VCHIQ_SERVICE_QUOTA_T *service_quota;

	service->closing = 1;

	/* Synchronise with other threads. */
	lmutex_lock(&state->recycle_mutex);
	lmutex_unlock(&state->recycle_mutex);
	if (!sh_thread || (state->conn_state != VCHIQ_CONNSTATE_PAUSE_SENT)) {
		/* If we're pausing then the slot_mutex is held until resume
		 * by the slot handler.  Therefore don't try to acquire this
		 * mutex if we're the slot handler and in the pause sent state.
		 * We don't need to in this case anyway. */
		lmutex_lock(&state->slot_mutex);
		lmutex_unlock(&state->slot_mutex);
	}

	/* Unblock any sending thread. */
	service_quota = &state->service_quotas[service->localport];
	up(&service_quota->quota_event);
}