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
struct ssif_info {int req_events; int /*<<< orphan*/  has_event_buffer; } ;

/* Variables and functions */
 unsigned long* ipmi_ssif_lock_cond (struct ssif_info*,unsigned long*) ; 
 int /*<<< orphan*/  ipmi_ssif_unlock_cond (struct ssif_info*,unsigned long*) ; 

__attribute__((used)) static void request_events(void *send_info)
{
	struct ssif_info *ssif_info = (struct ssif_info *) send_info;
	unsigned long oflags, *flags;

	if (!ssif_info->has_event_buffer)
		return;

	flags = ipmi_ssif_lock_cond(ssif_info, &oflags);
	ssif_info->req_events = true;
	ipmi_ssif_unlock_cond(ssif_info, flags);
}