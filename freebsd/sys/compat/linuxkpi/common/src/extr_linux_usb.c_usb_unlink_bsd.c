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
typedef  scalar_t__ uint8_t ;
struct usb_xfer {void* priv_fifo; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_drain (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_pending (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_start (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_stop (struct usb_xfer*) ; 

__attribute__((used)) static void
usb_unlink_bsd(struct usb_xfer *xfer,
    struct urb *urb, uint8_t drain)
{
	if (xfer == NULL)
		return;
	if (!usbd_transfer_pending(xfer))
		return;
	if (xfer->priv_fifo == (void *)urb) {
		if (drain) {
			mtx_unlock(&Giant);
			usbd_transfer_drain(xfer);
			mtx_lock(&Giant);
		} else {
			usbd_transfer_stop(xfer);
		}
		usbd_transfer_start(xfer);
	}
}