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
struct ssif_info {int msg_flags; int /*<<< orphan*/  ssif_state; int /*<<< orphan*/  intf; } ;

/* Variables and functions */
 int EVENT_MSG_BUFFER_FULL ; 
 int RECEIVE_MSG_AVAIL ; 
 int /*<<< orphan*/  SSIF_NORMAL ; 
 int WDT_PRE_TIMEOUT_INT ; 
 int /*<<< orphan*/  ipmi_smi_watchdog_pretimeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_ssif_unlock_cond (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  ssif_inc_stat (struct ssif_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_clear_flags (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  start_event_fetch (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  start_recv_msg_fetch (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  watchdog_pretimeouts ; 

__attribute__((used)) static void handle_flags(struct ssif_info *ssif_info, unsigned long *flags)
{
	if (ssif_info->msg_flags & WDT_PRE_TIMEOUT_INT) {
		/* Watchdog pre-timeout */
		ssif_inc_stat(ssif_info, watchdog_pretimeouts);
		start_clear_flags(ssif_info, flags);
		ipmi_smi_watchdog_pretimeout(ssif_info->intf);
	} else if (ssif_info->msg_flags & RECEIVE_MSG_AVAIL)
		/* Messages available. */
		start_recv_msg_fetch(ssif_info, flags);
	else if (ssif_info->msg_flags & EVENT_MSG_BUFFER_FULL)
		/* Events available. */
		start_event_fetch(ssif_info, flags);
	else {
		ssif_info->ssif_state = SSIF_NORMAL;
		ipmi_ssif_unlock_cond(ssif_info, flags);
	}
}