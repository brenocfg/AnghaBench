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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_host_endpoint {scalar_t__* bsd_xfer; int /*<<< orphan*/  bsd_urb_list; } ;
struct urb {scalar_t__ kill_count; int status; struct usb_host_endpoint* endpoint; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsd_urb_list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (scalar_t__) ; 

int
usb_submit_urb(struct urb *urb, uint16_t mem_flags)
{
	struct usb_host_endpoint *uhe;
	uint8_t do_unlock;
	int err;

	if (urb == NULL)
		return (-EINVAL);

	do_unlock = mtx_owned(&Giant) ? 0 : 1;
	if (do_unlock)
		mtx_lock(&Giant);

	if (urb->endpoint == NULL) {
		err = -EINVAL;
		goto done;
	}

	/*
	 * Check to see if the urb is in the process of being killed
	 * and stop a urb that is in the process of being killed from
	 * being re-submitted (e.g. from its completion callback
	 * function).
	 */
	if (urb->kill_count != 0) {
		err = -EPERM;
		goto done;
	}

	uhe = urb->endpoint;

	/*
	 * Check that we have got a FreeBSD USB transfer that will dequeue
	 * the URB structure and do the real transfer. If there are no USB
	 * transfers, then we return an error.
	 */
	if (uhe->bsd_xfer[0] ||
	    uhe->bsd_xfer[1]) {
		/* we are ready! */

		TAILQ_INSERT_TAIL(&uhe->bsd_urb_list, urb, bsd_urb_list);

		urb->status = -EINPROGRESS;

		usbd_transfer_start(uhe->bsd_xfer[0]);
		usbd_transfer_start(uhe->bsd_xfer[1]);
		err = 0;
	} else {
		/* no pipes have been setup yet! */
		urb->status = -EINVAL;
		err = -EINVAL;
	}
done:
	if (do_unlock)
		mtx_unlock(&Giant);
	return (err);
}