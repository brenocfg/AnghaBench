#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {int ctrl_tx_count; int ctrl_rx_count; int error_count; int slot_stalls; int data_stalls; } ;
struct TYPE_8__ {int id; size_t conn_state; int local_tx_pos; int rx_pos; int slot_queue_available; int data_quota; int data_use_count; int unused_service; TYPE_5__* remote; TYPE_5__* local; TYPE_1__ stats; scalar_t__ rx_data; scalar_t__ tx_data; } ;
typedef  TYPE_2__ VCHIQ_STATE_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_T ;
struct TYPE_9__ {int tx_pos; int slot_queue_recycle; } ;

/* Variables and functions */
 scalar_t__ VCHIQ_ENABLE_STATS ; 
 int VCHIQ_SLOT_MASK ; 
 int VCHIQ_SLOT_SIZE ; 
 int VCHIQ_VERSION ; 
 int VCHIQ_VERSION_MIN ; 
 char** conn_state_names ; 
 int /*<<< orphan*/ * find_service_by_port (TYPE_2__*,int) ; 
 int snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  unlock_service (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_dump (void*,char*,int) ; 
 int /*<<< orphan*/  vchiq_dump_platform_instances (void*) ; 
 int /*<<< orphan*/  vchiq_dump_platform_state (void*) ; 
 int /*<<< orphan*/  vchiq_dump_service_state (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_dump_shared_state (void*,TYPE_2__*,TYPE_5__*,char*) ; 

void
vchiq_dump_state(void *dump_context, VCHIQ_STATE_T *state)
{
	char buf[80];
	int len;
	int i;

	len = snprintf(buf, sizeof(buf), "State %d: %s", state->id,
		conn_state_names[state->conn_state]);
	vchiq_dump(dump_context, buf, len + 1);

	len = snprintf(buf, sizeof(buf),
		"  tx_pos=%x(@%x), rx_pos=%x(@%x)",
		state->local->tx_pos,
		(uint32_t)state->tx_data +
			(state->local_tx_pos & VCHIQ_SLOT_MASK),
		state->rx_pos,
		(uint32_t)state->rx_data +
			(state->rx_pos & VCHIQ_SLOT_MASK));
	vchiq_dump(dump_context, buf, len + 1);

	len = snprintf(buf, sizeof(buf),
		"  Version: %d (min %d)",
		VCHIQ_VERSION, VCHIQ_VERSION_MIN);
	vchiq_dump(dump_context, buf, len + 1);

	if (VCHIQ_ENABLE_STATS) {
		len = snprintf(buf, sizeof(buf),
			"  Stats: ctrl_tx_count=%d, ctrl_rx_count=%d, "
			"error_count=%d",
			state->stats.ctrl_tx_count, state->stats.ctrl_rx_count,
			state->stats.error_count);
		vchiq_dump(dump_context, buf, len + 1);
	}

	len = snprintf(buf, sizeof(buf),
		"  Slots: %d available (%d data), %d recyclable, %d stalls "
		"(%d data)",
		((state->slot_queue_available * VCHIQ_SLOT_SIZE) -
			state->local_tx_pos) / VCHIQ_SLOT_SIZE,
		state->data_quota - state->data_use_count,
		state->local->slot_queue_recycle - state->slot_queue_available,
		state->stats.slot_stalls, state->stats.data_stalls);
	vchiq_dump(dump_context, buf, len + 1);

	vchiq_dump_platform_state(dump_context);

	vchiq_dump_shared_state(dump_context, state, state->local, "Local");
	vchiq_dump_shared_state(dump_context, state, state->remote, "Remote");

	vchiq_dump_platform_instances(dump_context);

	for (i = 0; i < state->unused_service; i++) {
		VCHIQ_SERVICE_T *service = find_service_by_port(state, i);

		if (service) {
			vchiq_dump_service_state(dump_context, service);
			unlock_service(service);
		}
	}
}