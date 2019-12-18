#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  recycle_mutex; TYPE_1__* remote; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ VCHIQ_STATE_T ;
struct TYPE_14__ {int release_count; int use_count; } ;
typedef  TYPE_3__ VCHIQ_SLOT_INFO_T ;
struct TYPE_15__ {scalar_t__ closing; } ;
typedef  TYPE_4__ VCHIQ_SERVICE_T ;
struct TYPE_16__ {int msgid; } ;
typedef  TYPE_5__ VCHIQ_HEADER_T ;
struct TYPE_12__ {int slot_queue_recycle; int /*<<< orphan*/  recycle; int /*<<< orphan*/ * slot_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLOT_INDEX_FROM_INFO (TYPE_2__*,TYPE_3__*) ; 
 int VCHIQ_MSGID_CLAIMED ; 
 int VCHIQ_SLOT_QUEUE_MASK ; 
 int /*<<< orphan*/  lmutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lmutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
release_slot(VCHIQ_STATE_T *state, VCHIQ_SLOT_INFO_T *slot_info,
	VCHIQ_HEADER_T *header, VCHIQ_SERVICE_T *service)
{
	int release_count;

	lmutex_lock(&state->recycle_mutex);

	if (header) {
		int msgid = header->msgid;
		if (((msgid & VCHIQ_MSGID_CLAIMED) == 0) ||
			(service && service->closing)) {
			lmutex_unlock(&state->recycle_mutex);
			return;
		}

		/* Rewrite the message header to prevent a double
		** release */
		header->msgid = msgid & ~VCHIQ_MSGID_CLAIMED;
	}

	release_count = slot_info->release_count;
	slot_info->release_count = ++release_count;

	if (release_count == slot_info->use_count) {
		int slot_queue_recycle;
		/* Add to the freed queue */

		/* A read barrier is necessary here to prevent speculative
		** fetches of remote->slot_queue_recycle from overtaking the
		** mutex. */
		rmb();

		slot_queue_recycle = state->remote->slot_queue_recycle;
		state->remote->slot_queue[slot_queue_recycle &
			VCHIQ_SLOT_QUEUE_MASK] =
			SLOT_INDEX_FROM_INFO(state, slot_info);
		state->remote->slot_queue_recycle = slot_queue_recycle + 1;
		vchiq_log_info(vchiq_core_log_level,
			"%d: release_slot %d - recycle->%x",
			state->id, SLOT_INDEX_FROM_INFO(state, slot_info),
			state->remote->slot_queue_recycle);

		/* A write barrier is necessary, but remote_event_signal
		** contains one. */
		remote_event_signal(&state->remote->recycle);
	}

	lmutex_unlock(&state->recycle_mutex);
}