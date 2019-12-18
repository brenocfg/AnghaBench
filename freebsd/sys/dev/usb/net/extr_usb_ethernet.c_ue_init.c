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
struct usb_ether {TYPE_1__* ue_sync_task; } ;
struct TYPE_2__ {int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UE_LOCK (struct usb_ether*) ; 
 int /*<<< orphan*/  UE_UNLOCK (struct usb_ether*) ; 
 int /*<<< orphan*/  ue_queue_command (struct usb_ether*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ue_start_task ; 

__attribute__((used)) static void
ue_init(void *arg)
{
	struct usb_ether *ue = arg;

	UE_LOCK(ue);
	ue_queue_command(ue, ue_start_task,
	    &ue->ue_sync_task[0].hdr, 
	    &ue->ue_sync_task[1].hdr);
	UE_UNLOCK(ue);
}