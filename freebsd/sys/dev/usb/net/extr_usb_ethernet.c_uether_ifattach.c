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
struct usb_ether {TYPE_1__* ue_sync_task; int /*<<< orphan*/ * ue_dev; int /*<<< orphan*/ * ue_mtx; int /*<<< orphan*/  ue_tq; int /*<<< orphan*/ * ue_methods; int /*<<< orphan*/ * ue_udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UE_LOCK (struct usb_ether*) ; 
 int /*<<< orphan*/  UE_UNLOCK (struct usb_ether*) ; 
 int /*<<< orphan*/  USB_PRI_MED ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ue_attach_post_task ; 
 int /*<<< orphan*/  ue_queue_command (struct usb_ether*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int usb_proc_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
uether_ifattach(struct usb_ether *ue)
{
	int error;

	/* check some critical parameters */
	if ((ue->ue_dev == NULL) ||
	    (ue->ue_udev == NULL) ||
	    (ue->ue_mtx == NULL) ||
	    (ue->ue_methods == NULL))
		return (EINVAL);

	error = usb_proc_create(&ue->ue_tq, ue->ue_mtx, 
	    device_get_nameunit(ue->ue_dev), USB_PRI_MED);
	if (error) {
		device_printf(ue->ue_dev, "could not setup taskqueue\n");
		goto error;
	}

	/* fork rest of the attach code */
	UE_LOCK(ue);
	ue_queue_command(ue, ue_attach_post_task,
	    &ue->ue_sync_task[0].hdr,
	    &ue->ue_sync_task[1].hdr);
	UE_UNLOCK(ue);

error:
	return (error);
}