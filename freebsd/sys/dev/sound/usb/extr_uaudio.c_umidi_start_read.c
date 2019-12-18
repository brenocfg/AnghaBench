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
struct umidi_chan {int /*<<< orphan*/ * xfer; } ;

/* Variables and functions */
 size_t UMIDI_RX_TRANSFER ; 
 struct umidi_chan* usb_fifo_softc (struct usb_fifo*) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
umidi_start_read(struct usb_fifo *fifo)
{
	struct umidi_chan *chan = usb_fifo_softc(fifo);

	usbd_transfer_start(chan->xfer[UMIDI_RX_TRANSFER]);
}