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
struct usb_data_xfer_block {int blen; int ccs; scalar_t__ bdone; scalar_t__ processed; void* hci_data; void* buf; } ;
struct usb_data_xfer {int ndata; size_t tail; struct usb_data_xfer_block* data; } ;

/* Variables and functions */
 int USB_MAX_XFER_BLOCKS ; 

struct usb_data_xfer_block *
usb_data_xfer_append(struct usb_data_xfer *xfer, void *buf, int blen,
                     void *hci_data, int ccs)
{
	struct usb_data_xfer_block *xb;

	if (xfer->ndata >= USB_MAX_XFER_BLOCKS)
		return (NULL);

	xb = &xfer->data[xfer->tail];
	xb->buf = buf;
	xb->blen = blen;
	xb->hci_data = hci_data;
	xb->ccs = ccs;
	xb->processed = 0;
	xb->bdone = 0;
	xfer->ndata++;
	xfer->tail = (xfer->tail + 1) % USB_MAX_XFER_BLOCKS;
	return (xb);
}