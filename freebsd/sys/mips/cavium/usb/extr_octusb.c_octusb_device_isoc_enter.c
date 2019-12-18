#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct usb_xfer {int nframes; TYPE_3__* endpoint; scalar_t__ isoc_time_complete; TYPE_2__* xroot; } ;
struct octusb_softc {int /*<<< orphan*/  sc_bus; TYPE_1__* sc_port; } ;
struct TYPE_8__ {size_t port_index; } ;
struct TYPE_7__ {int isoc_next; int is_synced; } ;
struct TYPE_6__ {TYPE_4__* udev; int /*<<< orphan*/  bus; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 struct octusb_softc* OCTUSB_BUS2SC (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int cvmx_usb_get_frame_number (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_isoc_time_expand (int /*<<< orphan*/ *,int) ; 
 scalar_t__ usbd_get_speed (TYPE_4__*) ; 

__attribute__((used)) static void
octusb_device_isoc_enter(struct usb_xfer *xfer)
{
	struct octusb_softc *sc = OCTUSB_BUS2SC(xfer->xroot->bus);
	uint32_t temp;
	uint32_t frame_count;
	uint32_t fs_frames;

	DPRINTFN(5, "xfer=%p next=%d nframes=%d\n",
	    xfer, xfer->endpoint->isoc_next, xfer->nframes);

	/* get the current frame index */

	frame_count = cvmx_usb_get_frame_number(
	    &sc->sc_port[xfer->xroot->udev->port_index].state);

	/*
	 * check if the frame index is within the window where the frames
	 * will be inserted
	 */
	temp = (frame_count - xfer->endpoint->isoc_next) & 0x7FF;

	if (usbd_get_speed(xfer->xroot->udev) == USB_SPEED_HIGH) {
		fs_frames = (xfer->nframes + 7) / 8;
	} else {
		fs_frames = xfer->nframes;
	}

	if ((xfer->endpoint->is_synced == 0) || (temp < fs_frames)) {
		/*
		 * If there is data underflow or the pipe queue is
		 * empty we schedule the transfer a few frames ahead
		 * of the current frame position. Else two isochronous
		 * transfers might overlap.
		 */
		xfer->endpoint->isoc_next = (frame_count + 3) & 0x7FF;
		xfer->endpoint->is_synced = 1;
		DPRINTFN(2, "start next=%d\n", xfer->endpoint->isoc_next);
	}
	/*
	 * compute how many milliseconds the insertion is ahead of the
	 * current frame position:
	 */
	temp = (xfer->endpoint->isoc_next - frame_count) & 0x7FF;

	/*
	 * pre-compute when the isochronous transfer will be finished:
	 */
	xfer->isoc_time_complete =
	    usb_isoc_time_expand(&sc->sc_bus, frame_count) + temp +
	    fs_frames;

	/* compute frame number for next insertion */
	xfer->endpoint->isoc_next += fs_frames;
}