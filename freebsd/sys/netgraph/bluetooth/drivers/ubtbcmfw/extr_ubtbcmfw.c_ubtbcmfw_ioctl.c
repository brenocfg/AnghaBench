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
typedef  int u_long ;
struct usb_fifo {int dummy; } ;
struct usb_device_descriptor {int dummy; } ;
struct ubtbcmfw_softc {int /*<<< orphan*/  sc_udev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USB_GET_DEVICE_DESC 128 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 struct ubtbcmfw_softc* usb_fifo_softc (struct usb_fifo*) ; 
 int /*<<< orphan*/  usbd_get_device_descriptor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ubtbcmfw_ioctl(struct usb_fifo *fifo, u_long cmd, void *data,
    int fflags)
{
	struct ubtbcmfw_softc	*sc = usb_fifo_softc(fifo);
	int			error = 0;

	switch (cmd) {
	case USB_GET_DEVICE_DESC:
		memcpy(data, usbd_get_device_descriptor(sc->sc_udev),
			sizeof(struct usb_device_descriptor));
		break;

	default:
		error = EINVAL;
		break;
	}

	return (error);
}