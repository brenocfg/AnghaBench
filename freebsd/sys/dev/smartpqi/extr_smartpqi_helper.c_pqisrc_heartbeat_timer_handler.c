#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {scalar_t__ prev_heartbeat_count; scalar_t__ prev_num_intrs; scalar_t__ num_heartbeats_requested; TYPE_1__* pending_events; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;
struct TYPE_9__ {int pending; } ;

/* Variables and functions */
 scalar_t__ CTRLR_HEARTBEAT_CNT (TYPE_2__*) ; 
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_INFO (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ OS_ATOMIC64_READ (TYPE_2__*,scalar_t__) ; 
 size_t PQI_EVENT_HEARTBEAT ; 
 scalar_t__ PQI_MAX_HEARTBEAT_REQUESTS ; 
 scalar_t__ PQI_NEW_HEARTBEAT_MECHANISM (TYPE_2__*) ; 
 int /*<<< orphan*/  os_stop_heartbeat_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  pqisrc_ack_all_events (void*) ; 
 int /*<<< orphan*/  pqisrc_take_ctrl_offline (TYPE_2__*) ; 

void pqisrc_heartbeat_timer_handler(pqisrc_softstate_t *softs)
{
	uint64_t num_intrs;
	uint8_t take_offline = false;

	DBG_FUNC("IN\n");

	num_intrs = OS_ATOMIC64_READ(softs, num_intrs);

	if (PQI_NEW_HEARTBEAT_MECHANISM(softs)) {
		if (CTRLR_HEARTBEAT_CNT(softs) == softs->prev_heartbeat_count) {
			take_offline = true;
			goto take_ctrl_offline;
		}
		softs->prev_heartbeat_count = CTRLR_HEARTBEAT_CNT(softs);
		DBG_INFO("CTRLR_HEARTBEAT_CNT(softs)  = %lx \
		softs->prev_heartbeat_count = %lx\n",
		CTRLR_HEARTBEAT_CNT(softs), softs->prev_heartbeat_count);
	} else {
		if (num_intrs == softs->prev_num_intrs) {
			softs->num_heartbeats_requested++;
			if (softs->num_heartbeats_requested > PQI_MAX_HEARTBEAT_REQUESTS) {
				take_offline = true;
				goto take_ctrl_offline;
			}
			softs->pending_events[PQI_EVENT_HEARTBEAT].pending = true;

			pqisrc_ack_all_events((void*)softs);

		} else {
			softs->num_heartbeats_requested = 0;
		}
		softs->prev_num_intrs = num_intrs;
	}

take_ctrl_offline:
	if (take_offline){
		DBG_ERR("controller is offline\n");
		pqisrc_take_ctrl_offline(softs);
		os_stop_heartbeat_timer(softs);
	}
	DBG_FUNC("OUT\n");
}