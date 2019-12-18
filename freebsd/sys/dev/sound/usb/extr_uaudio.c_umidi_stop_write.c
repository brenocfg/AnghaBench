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
struct usb_fifo {int dummy; } ;
struct umidi_sub_chan {scalar_t__ write_open; } ;
struct umidi_chan {scalar_t__ write_open_refcount; int /*<<< orphan*/ * xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 size_t UMIDI_TX_TRANSFER ; 
 struct umidi_sub_chan* umidi_sub_by_fifo (struct usb_fifo*) ; 
 struct umidi_chan* usb_fifo_softc (struct usb_fifo*) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
umidi_stop_write(struct usb_fifo *fifo)
{
	struct umidi_chan *chan = usb_fifo_softc(fifo);
	struct umidi_sub_chan *sub = umidi_sub_by_fifo(fifo);

	DPRINTF("\n");

	sub->write_open = 0;

	if (--(chan->write_open_refcount) == 0) {
		DPRINTF("(stopping write transfer)\n");
		usbd_transfer_stop(chan->xfer[UMIDI_TX_TRANSFER]);
	}
}