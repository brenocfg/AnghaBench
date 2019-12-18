#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  VCHIQ_STATE_T ;
struct TYPE_5__ {scalar_t__ use_count; scalar_t__ release_count; } ;
typedef  TYPE_1__ VCHIQ_SLOT_INFO_T ;
struct TYPE_6__ {int slot_first; int slot_last; int tx_pos; int slot_queue_recycle; int* debug; } ;
typedef  TYPE_2__ VCHIQ_SHARED_STATE_T ;

/* Variables and functions */
 size_t DEBUG_ENTRIES ; 
 TYPE_1__* SLOT_INFO_FROM_INDEX (int /*<<< orphan*/ *,int) ; 
 int snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  vchiq_dump (void*,char*,int) ; 

__attribute__((used)) static void
vchiq_dump_shared_state(void *dump_context, VCHIQ_STATE_T *state,
	VCHIQ_SHARED_STATE_T *shared, const char *label)
{
	static const char *const debug_names[] = {
		"<entries>",
		"SLOT_HANDLER_COUNT",
		"SLOT_HANDLER_LINE",
		"PARSE_LINE",
		"PARSE_HEADER",
		"PARSE_MSGID",
		"AWAIT_COMPLETION_LINE",
		"DEQUEUE_MESSAGE_LINE",
		"SERVICE_CALLBACK_LINE",
		"MSG_QUEUE_FULL_COUNT",
		"COMPLETION_QUEUE_FULL_COUNT"
	};
	int i;

	char buf[80];
	int len;
	len = snprintf(buf, sizeof(buf),
		"  %s: slots %d-%d tx_pos=%x recycle=%x",
		label, shared->slot_first, shared->slot_last,
		shared->tx_pos, shared->slot_queue_recycle);
	vchiq_dump(dump_context, buf, len + 1);

	len = snprintf(buf, sizeof(buf),
		"    Slots claimed:");
	vchiq_dump(dump_context, buf, len + 1);

	for (i = shared->slot_first; i <= shared->slot_last; i++) {
		VCHIQ_SLOT_INFO_T slot_info = *SLOT_INFO_FROM_INDEX(state, i);
		if (slot_info.use_count != slot_info.release_count) {
			len = snprintf(buf, sizeof(buf),
				"      %d: %d/%d", i, slot_info.use_count,
				slot_info.release_count);
			vchiq_dump(dump_context, buf, len + 1);
		}
	}

	for (i = 1; i < shared->debug[DEBUG_ENTRIES]; i++) {
		len = snprintf(buf, sizeof(buf), "    DEBUG: %s = %d(%x)",
			debug_names[i], shared->debug[i], shared->debug[i]);
		vchiq_dump(dump_context, buf, len + 1);
	}
}