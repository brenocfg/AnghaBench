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
struct usb_linux_softc {int /*<<< orphan*/  sc_ui; } ;
struct usb_driver {int (* resume ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct usb_linux_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 struct usb_driver* usb_linux_get_usb_driver (struct usb_linux_softc*) ; 

__attribute__((used)) static int
usb_linux_resume(device_t dev)
{
	struct usb_linux_softc *sc = device_get_softc(dev);
	struct usb_driver *udrv = usb_linux_get_usb_driver(sc);
	int err;

	if (udrv && udrv->resume) {
		err = (udrv->resume) (sc->sc_ui);
	}
	return (0);
}