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
struct umidi_sub_chan {int read_open; int write_open; int /*<<< orphan*/  state; } ;
struct umidi_chan {int /*<<< orphan*/  mtx; int /*<<< orphan*/  write_open_refcount; int /*<<< orphan*/  read_open_refcount; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  UMIDI_ST_UNKNOWN ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct umidi_sub_chan* umidi_sub_by_fifo (struct usb_fifo*) ; 
 scalar_t__ usb_fifo_alloc_buffer (struct usb_fifo*,int,int) ; 
 struct umidi_chan* usb_fifo_softc (struct usb_fifo*) ; 

__attribute__((used)) static int
umidi_open(struct usb_fifo *fifo, int fflags)
{
	struct umidi_chan *chan = usb_fifo_softc(fifo);
	struct umidi_sub_chan *sub = umidi_sub_by_fifo(fifo);

	if (fflags & FREAD) {
		if (usb_fifo_alloc_buffer(fifo, 4, (1024 / 4))) {
			return (ENOMEM);
		}
		mtx_lock(&chan->mtx);
		chan->read_open_refcount++;
		sub->read_open = 1;
		mtx_unlock(&chan->mtx);
	}
	if (fflags & FWRITE) {
		if (usb_fifo_alloc_buffer(fifo, 32, (1024 / 32))) {
			return (ENOMEM);
		}
		/* clear stall first */
		mtx_lock(&chan->mtx);
		chan->write_open_refcount++;
		sub->write_open = 1;

		/* reset */
		sub->state = UMIDI_ST_UNKNOWN;
		mtx_unlock(&chan->mtx);
	}
	return (0);			/* success */
}