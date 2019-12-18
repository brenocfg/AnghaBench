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
struct usb_proc_msg {int dummy; } ;
struct usb_ether_cfg_task {struct usb_ether* ue; } ;
struct usb_ether {TYPE_1__* ue_methods; int /*<<< orphan*/  ue_watchdog; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ue_stop ) (struct usb_ether*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  UE_LOCK_ASSERT (struct usb_ether*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_ether*) ; 
 int /*<<< orphan*/  usb_callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ue_stop_task(struct usb_proc_msg *_task)
{
	struct usb_ether_cfg_task *task =
	    (struct usb_ether_cfg_task *)_task;
	struct usb_ether *ue = task->ue;

	UE_LOCK_ASSERT(ue, MA_OWNED);

	usb_callout_stop(&ue->ue_watchdog);

	ue->ue_methods->ue_stop(ue);
}