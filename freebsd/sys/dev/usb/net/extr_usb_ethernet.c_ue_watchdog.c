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
struct usb_ether {int /*<<< orphan*/  ue_watchdog; TYPE_1__* ue_tick_task; struct ifnet* ue_ifp; } ;
struct ifnet {int if_drv_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ue_queue_command (struct usb_ether*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ue_tick_task ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct usb_ether*) ; 

__attribute__((used)) static void
ue_watchdog(void *arg)
{
	struct usb_ether *ue = arg;
	struct ifnet *ifp = ue->ue_ifp;

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;

	ue_queue_command(ue, ue_tick_task,
	    &ue->ue_tick_task[0].hdr, 
	    &ue->ue_tick_task[1].hdr);

	usb_callout_reset(&ue->ue_watchdog, hz, ue_watchdog, ue);
}