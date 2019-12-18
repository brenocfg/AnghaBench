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
struct usb_xfer {int dummy; } ;
struct usb_fifo {int dummy; } ;
struct ubtbcmfw_softc {struct usb_xfer** sc_xfer; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FREAD ; 
 int FWRITE ; 
 size_t UBTBCMFW_BULK_DT_WR ; 
 int /*<<< orphan*/  UBTBCMFW_IFQ_MAXLEN ; 
 size_t UBTBCMFW_INTR_DT_RD ; 
 scalar_t__ usb_fifo_alloc_buffer (struct usb_fifo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ubtbcmfw_softc* usb_fifo_softc (struct usb_fifo*) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 

__attribute__((used)) static int
ubtbcmfw_open(struct usb_fifo *fifo, int fflags)
{
	struct ubtbcmfw_softc	*sc = usb_fifo_softc(fifo);
	struct usb_xfer	*xfer;

	/*
	 * f_open fifo method can only be called with either FREAD
	 * or FWRITE flag set at one time.
	 */

	if (fflags & FREAD)
		xfer = sc->sc_xfer[UBTBCMFW_INTR_DT_RD];
	else if (fflags & FWRITE)
		xfer = sc->sc_xfer[UBTBCMFW_BULK_DT_WR];
	else
		return (EINVAL);	/* should not happen */

	if (usb_fifo_alloc_buffer(fifo, usbd_xfer_max_len(xfer),
			UBTBCMFW_IFQ_MAXLEN) != 0)
		return (ENOMEM);

	return (0);
}