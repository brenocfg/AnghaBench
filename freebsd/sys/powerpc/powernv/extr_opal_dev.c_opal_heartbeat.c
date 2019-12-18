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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSEC_2_TICKS (scalar_t__) ; 
 int OPAL_EVENT_MSG_PENDING ; 
 int /*<<< orphan*/  OPAL_POLL_EVENTS ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opal_handle_messages () ; 
 int /*<<< orphan*/  opal_hb_proc ; 
 scalar_t__ opal_heartbeat_ms ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtophys (int*) ; 

__attribute__((used)) static void
opal_heartbeat(void)
{
	uint64_t events;

	if (opal_heartbeat_ms == 0)
		kproc_exit(0);

	while (1) {
		events = 0;
		/* Turn the OPAL state crank */
		opal_call(OPAL_POLL_EVENTS, vtophys(&events));
		if (events & OPAL_EVENT_MSG_PENDING)
			opal_handle_messages();
		tsleep(opal_hb_proc, 0, "opal",
		    MSEC_2_TICKS(opal_heartbeat_ms));
	}
}