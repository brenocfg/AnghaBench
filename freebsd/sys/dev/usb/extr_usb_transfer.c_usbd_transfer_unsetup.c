#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uint16_t ;
struct usb_xfer_root {scalar_t__ setup_refcount; int /*<<< orphan*/  bus; } ;
struct TYPE_3__ {scalar_t__ bdma_enable; } ;
struct usb_xfer {int /*<<< orphan*/  timeout_handle; TYPE_2__* endpoint; TYPE_1__ flags_int; struct usb_xfer_root* xroot; } ;
struct TYPE_4__ {int /*<<< orphan*/  refcount_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ASSERT (int,char*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_XFER_LOCK (struct usb_xfer*) ; 
 int /*<<< orphan*/  USB_XFER_UNLOCK (struct usb_xfer*) ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_drain (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup_sub (struct usb_xfer_root*,int) ; 

void
usbd_transfer_unsetup(struct usb_xfer **pxfer, uint16_t n_setup)
{
	struct usb_xfer *xfer;
	struct usb_xfer_root *info;
	uint8_t needs_delay = 0;

	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
	    "usbd_transfer_unsetup can sleep!");

	while (n_setup--) {
		xfer = pxfer[n_setup];

		if (xfer == NULL)
			continue;

		info = xfer->xroot;

		USB_XFER_LOCK(xfer);
		USB_BUS_LOCK(info->bus);

		/*
		 * HINT: when you start/stop a transfer, it might be a
		 * good idea to directly use the "pxfer[]" structure:
		 *
		 * usbd_transfer_start(sc->pxfer[0]);
		 * usbd_transfer_stop(sc->pxfer[0]);
		 *
		 * That way, if your code has many parts that will not
		 * stop running under the same lock, in other words
		 * "xfer_mtx", the usbd_transfer_start and
		 * usbd_transfer_stop functions will simply return
		 * when they detect a NULL pointer argument.
		 *
		 * To avoid any races we clear the "pxfer[]" pointer
		 * while holding the private mutex of the driver:
		 */
		pxfer[n_setup] = NULL;

		USB_BUS_UNLOCK(info->bus);
		USB_XFER_UNLOCK(xfer);

		usbd_transfer_drain(xfer);

#if USB_HAVE_BUSDMA
		if (xfer->flags_int.bdma_enable)
			needs_delay = 1;
#endif
		/*
		 * NOTE: default endpoint does not have an
		 * interface, even if endpoint->iface_index == 0
		 */
		USB_BUS_LOCK(info->bus);
		xfer->endpoint->refcount_alloc--;
		USB_BUS_UNLOCK(info->bus);

		usb_callout_drain(&xfer->timeout_handle);

		USB_BUS_LOCK(info->bus);

		USB_ASSERT(info->setup_refcount != 0, ("Invalid setup "
		    "reference count\n"));

		info->setup_refcount--;

		if (info->setup_refcount == 0) {
			usbd_transfer_unsetup_sub(info,
			    needs_delay);
		} else {
			USB_BUS_UNLOCK(info->bus);
		}
	}
}