#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t usb_frcount_t ;
struct usb_xfer_root {int /*<<< orphan*/  dma_q; TYPE_2__* udev; struct usb_bus* bus; } ;
struct TYPE_9__ {int open; int transferring; int can_cancel_immed; int short_xfer_ok; int short_frames_ok; scalar_t__ bdma_enable; scalar_t__ control_xfr; scalar_t__ bdma_setup; scalar_t__ did_close; scalar_t__ did_dma_delay; } ;
struct TYPE_8__ {scalar_t__ short_xfer_ok; scalar_t__ short_frames_ok; scalar_t__ stall_pipe; } ;
struct usb_xfer {scalar_t__ nframes; scalar_t__ sumlen; size_t stream_id; scalar_t__* frlengths; size_t max_frame_count; struct usb_xfer_root* xroot; TYPE_4__ flags_int; TYPE_3__ flags; TYPE_5__* endpoint; scalar_t__ error; scalar_t__ aframes; scalar_t__ actlen; scalar_t__ wait_queue; } ;
struct usb_bus {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/ * endpoint_q; TYPE_1__* methods; } ;
struct TYPE_7__ {scalar_t__ state; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* open ) (struct usb_xfer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (struct usb_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 scalar_t__ USB_DEBUG_VAR ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int /*<<< orphan*/  USB_ERR_INVAL ; 
 int /*<<< orphan*/  USB_ERR_STALLED ; 
 scalar_t__ USB_GET_DATA_ISREAD (struct usb_xfer*) ; 
 scalar_t__ USB_STATE_POWERED ; 
 int /*<<< orphan*/  USB_XFER_LOCK_ASSERT (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_xfer*) ; 
 int /*<<< orphan*/  usb_command_wrapper (int /*<<< orphan*/ *,struct usb_xfer*) ; 
 int /*<<< orphan*/  usb_dump_endpoint (TYPE_5__*) ; 
 int /*<<< orphan*/  usbd_pipe_enter (struct usb_xfer*) ; 
 scalar_t__ usbd_setup_ctrl_transfer (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_dequeue (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_power_ref (struct usb_xfer*,int) ; 

void
usbd_transfer_submit(struct usb_xfer *xfer)
{
	struct usb_xfer_root *info;
	struct usb_bus *bus;
	usb_frcount_t x;

	info = xfer->xroot;
	bus = info->bus;

	DPRINTF("xfer=%p, endpoint=%p, nframes=%d, dir=%s\n",
	    xfer, xfer->endpoint, xfer->nframes, USB_GET_DATA_ISREAD(xfer) ?
	    "read" : "write");

#ifdef USB_DEBUG
	if (USB_DEBUG_VAR > 0) {
		USB_BUS_LOCK(bus);

		usb_dump_endpoint(xfer->endpoint);

		USB_BUS_UNLOCK(bus);
	}
#endif

	USB_XFER_LOCK_ASSERT(xfer, MA_OWNED);
	USB_BUS_LOCK_ASSERT(bus, MA_NOTOWNED);

	/* Only open the USB transfer once! */
	if (!xfer->flags_int.open) {
		xfer->flags_int.open = 1;

		DPRINTF("open\n");

		USB_BUS_LOCK(bus);
		(xfer->endpoint->methods->open) (xfer);
		USB_BUS_UNLOCK(bus);
	}
	/* set "transferring" flag */
	xfer->flags_int.transferring = 1;

#if USB_HAVE_POWERD
	/* increment power reference */
	usbd_transfer_power_ref(xfer, 1);
#endif
	/*
	 * Check if the transfer is waiting on a queue, most
	 * frequently the "done_q":
	 */
	if (xfer->wait_queue) {
		USB_BUS_LOCK(bus);
		usbd_transfer_dequeue(xfer);
		USB_BUS_UNLOCK(bus);
	}
	/* clear "did_dma_delay" flag */
	xfer->flags_int.did_dma_delay = 0;

	/* clear "did_close" flag */
	xfer->flags_int.did_close = 0;

#if USB_HAVE_BUSDMA
	/* clear "bdma_setup" flag */
	xfer->flags_int.bdma_setup = 0;
#endif
	/* by default we cannot cancel any USB transfer immediately */
	xfer->flags_int.can_cancel_immed = 0;

	/* clear lengths and frame counts by default */
	xfer->sumlen = 0;
	xfer->actlen = 0;
	xfer->aframes = 0;

	/* clear any previous errors */
	xfer->error = 0;

	/* Check if the device is still alive */
	if (info->udev->state < USB_STATE_POWERED) {
		USB_BUS_LOCK(bus);
		/*
		 * Must return cancelled error code else
		 * device drivers can hang.
		 */
		usbd_transfer_done(xfer, USB_ERR_CANCELLED);
		USB_BUS_UNLOCK(bus);
		return;
	}

	/* sanity check */
	if (xfer->nframes == 0) {
		if (xfer->flags.stall_pipe) {
			/*
			 * Special case - want to stall without transferring
			 * any data:
			 */
			DPRINTF("xfer=%p nframes=0: stall "
			    "or clear stall!\n", xfer);
			USB_BUS_LOCK(bus);
			xfer->flags_int.can_cancel_immed = 1;
			/* start the transfer */
			usb_command_wrapper(&xfer->endpoint->
			    endpoint_q[xfer->stream_id], xfer);
			USB_BUS_UNLOCK(bus);
			return;
		}
		USB_BUS_LOCK(bus);
		usbd_transfer_done(xfer, USB_ERR_INVAL);
		USB_BUS_UNLOCK(bus);
		return;
	}
	/* compute some variables */

	for (x = 0; x != xfer->nframes; x++) {
		/* make a copy of the frlenghts[] */
		xfer->frlengths[x + xfer->max_frame_count] = xfer->frlengths[x];
		/* compute total transfer length */
		xfer->sumlen += xfer->frlengths[x];
		if (xfer->sumlen < xfer->frlengths[x]) {
			/* length wrapped around */
			USB_BUS_LOCK(bus);
			usbd_transfer_done(xfer, USB_ERR_INVAL);
			USB_BUS_UNLOCK(bus);
			return;
		}
	}

	/* clear some internal flags */

	xfer->flags_int.short_xfer_ok = 0;
	xfer->flags_int.short_frames_ok = 0;

	/* check if this is a control transfer */

	if (xfer->flags_int.control_xfr) {

		if (usbd_setup_ctrl_transfer(xfer)) {
			USB_BUS_LOCK(bus);
			usbd_transfer_done(xfer, USB_ERR_STALLED);
			USB_BUS_UNLOCK(bus);
			return;
		}
	}
	/*
	 * Setup filtered version of some transfer flags,
	 * in case of data read direction
	 */
	if (USB_GET_DATA_ISREAD(xfer)) {

		if (xfer->flags.short_frames_ok) {
			xfer->flags_int.short_xfer_ok = 1;
			xfer->flags_int.short_frames_ok = 1;
		} else if (xfer->flags.short_xfer_ok) {
			xfer->flags_int.short_xfer_ok = 1;

			/* check for control transfer */
			if (xfer->flags_int.control_xfr) {
				/*
				 * 1) Control transfers do not support
				 * reception of multiple short USB
				 * frames in host mode and device side
				 * mode, with exception of:
				 *
				 * 2) Due to sometimes buggy device
				 * side firmware we need to do a
				 * STATUS stage in case of short
				 * control transfers in USB host mode.
				 * The STATUS stage then becomes the
				 * "alt_next" to the DATA stage.
				 */
				xfer->flags_int.short_frames_ok = 1;
			}
		}
	}
	/*
	 * Check if BUS-DMA support is enabled and try to load virtual
	 * buffers into DMA, if any:
	 */
#if USB_HAVE_BUSDMA
	if (xfer->flags_int.bdma_enable) {
		/* insert the USB transfer last in the BUS-DMA queue */
		usb_command_wrapper(&xfer->xroot->dma_q, xfer);
		return;
	}
#endif
	/*
	 * Enter the USB transfer into the Host Controller or
	 * Device Controller schedule:
	 */
	usbd_pipe_enter(xfer);
}