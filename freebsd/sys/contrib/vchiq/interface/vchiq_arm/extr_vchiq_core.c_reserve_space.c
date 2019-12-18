#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int local_tx_pos; char* tx_data; int slot_queue_available; int /*<<< orphan*/  slot_available_event; TYPE_1__* remote; TYPE_3__* local; } ;
typedef  TYPE_2__ VCHIQ_STATE_T ;
struct TYPE_11__ {int tx_pos; int* slot_queue; } ;
typedef  TYPE_3__ VCHIQ_SHARED_STATE_T ;
struct TYPE_12__ {int size; int /*<<< orphan*/  msgid; } ;
typedef  TYPE_4__ VCHIQ_HEADER_T ;
struct TYPE_9__ {int /*<<< orphan*/  trigger; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ SLOT_DATA_FROM_INDEX (TYPE_2__*,int) ; 
 size_t SLOT_QUEUE_INDEX_FROM_POS (int) ; 
 int /*<<< orphan*/  VCHIQ_MSGID_PADDING ; 
 int VCHIQ_SLOT_MASK ; 
 size_t VCHIQ_SLOT_QUEUE_MASK ; 
 int VCHIQ_SLOT_SIZE ; 
 int /*<<< orphan*/  VCHIQ_STATS_INC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slot_stalls ; 

__attribute__((used)) static VCHIQ_HEADER_T *
reserve_space(VCHIQ_STATE_T *state, int space, int is_blocking)
{
	VCHIQ_SHARED_STATE_T *local = state->local;
	int tx_pos = state->local_tx_pos;
	int slot_space = VCHIQ_SLOT_SIZE - (tx_pos & VCHIQ_SLOT_MASK);

	if (space > slot_space) {
		VCHIQ_HEADER_T *header;
		/* Fill the remaining space with padding */
		WARN_ON(state->tx_data == NULL);
		header = (VCHIQ_HEADER_T *)
			(state->tx_data + (tx_pos & VCHIQ_SLOT_MASK));
		header->msgid = VCHIQ_MSGID_PADDING;
		header->size = slot_space - sizeof(VCHIQ_HEADER_T);

		tx_pos += slot_space;
	}

	/* If necessary, get the next slot. */
	if ((tx_pos & VCHIQ_SLOT_MASK) == 0) {
		int slot_index;

		/* If there is no free slot... */

		if (down_trylock(&state->slot_available_event) != 0) {
			/* ...wait for one. */

			VCHIQ_STATS_INC(state, slot_stalls);

			/* But first, flush through the last slot. */
			state->local_tx_pos = tx_pos;
			local->tx_pos = tx_pos;
			remote_event_signal(&state->remote->trigger);

			if (!is_blocking ||
				(down_interruptible(
				&state->slot_available_event) != 0))
				return NULL; /* No space available */
		}

		BUG_ON(tx_pos ==
			(state->slot_queue_available * VCHIQ_SLOT_SIZE));

		slot_index = local->slot_queue[
			SLOT_QUEUE_INDEX_FROM_POS(tx_pos) &
			VCHIQ_SLOT_QUEUE_MASK];
		state->tx_data =
			(char *)SLOT_DATA_FROM_INDEX(state, slot_index);
	}

	state->local_tx_pos = tx_pos + space;

	return (VCHIQ_HEADER_T *)(state->tx_data + (tx_pos & VCHIQ_SLOT_MASK));
}