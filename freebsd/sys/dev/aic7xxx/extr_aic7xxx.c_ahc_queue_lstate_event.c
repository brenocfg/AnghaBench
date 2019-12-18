#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u_int ;
struct ahc_tmode_lstate {scalar_t__ event_w_idx; scalar_t__ event_r_idx; struct ahc_tmode_event* event_buffer; int /*<<< orphan*/  path; } ;
struct ahc_tmode_event {int event_type; int event_arg; scalar_t__ initiator_id; } ;
struct ahc_softc {int dummy; } ;

/* Variables and functions */
 int AHC_TMODE_EVENT_BUFFER_SIZE ; 
 scalar_t__ EVENT_TYPE_BUS_RESET ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MSG_BUS_DEV_RESET ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_print_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_devq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahc_queue_lstate_event(struct ahc_softc *ahc, struct ahc_tmode_lstate *lstate,
		       u_int initiator_id, u_int event_type, u_int event_arg)
{
	struct ahc_tmode_event *event;
	int pending;

	xpt_freeze_devq(lstate->path, /*count*/1);
	if (lstate->event_w_idx >= lstate->event_r_idx)
		pending = lstate->event_w_idx - lstate->event_r_idx;
	else
		pending = AHC_TMODE_EVENT_BUFFER_SIZE + 1
			- (lstate->event_r_idx - lstate->event_w_idx);

	if (event_type == EVENT_TYPE_BUS_RESET
	 || event_type == MSG_BUS_DEV_RESET) {
		/*
		 * Any earlier events are irrelevant, so reset our buffer.
		 * This has the effect of allowing us to deal with reset
		 * floods (an external device holding down the reset line)
		 * without losing the event that is really interesting.
		 */
		lstate->event_r_idx = 0;
		lstate->event_w_idx = 0;
		xpt_release_devq(lstate->path, pending, /*runqueue*/FALSE);
	}

	if (pending == AHC_TMODE_EVENT_BUFFER_SIZE) {
		xpt_print_path(lstate->path);
		printf("immediate event %x:%x lost\n",
		       lstate->event_buffer[lstate->event_r_idx].event_type,
		       lstate->event_buffer[lstate->event_r_idx].event_arg);
		lstate->event_r_idx++;
		if (lstate->event_r_idx == AHC_TMODE_EVENT_BUFFER_SIZE)
			lstate->event_r_idx = 0;
		xpt_release_devq(lstate->path, /*count*/1, /*runqueue*/FALSE);
	}

	event = &lstate->event_buffer[lstate->event_w_idx];
	event->initiator_id = initiator_id;
	event->event_type = event_type;
	event->event_arg = event_arg;
	lstate->event_w_idx++;
	if (lstate->event_w_idx == AHC_TMODE_EVENT_BUFFER_SIZE)
		lstate->event_w_idx = 0;
}