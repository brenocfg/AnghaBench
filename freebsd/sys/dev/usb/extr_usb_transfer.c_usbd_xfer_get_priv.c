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
struct usb_xfer {void* priv_fifo; } ;

/* Variables and functions */

void *
usbd_xfer_get_priv(struct usb_xfer *xfer)
{
	return (xfer->priv_fifo);
}