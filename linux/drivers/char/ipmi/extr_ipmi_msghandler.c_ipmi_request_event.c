#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipmi_smi {int /*<<< orphan*/  send_info; TYPE_1__* handlers; int /*<<< orphan*/  in_shutdown; scalar_t__ maintenance_mode_enable; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* request_events ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipmi_request_event(struct ipmi_smi *intf)
{
	/* No event requests when in maintenance mode. */
	if (intf->maintenance_mode_enable)
		return;

	if (!intf->in_shutdown)
		intf->handlers->request_events(intf->send_info);
}