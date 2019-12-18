#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * le_prev; } ;
struct usb_linux_softc {int /*<<< orphan*/  sc_ui; int /*<<< orphan*/  sc_fbsd_udev; struct usb_driver* sc_udrv; TYPE_1__ sc_attached_list; } ;
struct usb_driver {int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  LIST_REMOVE (struct usb_linux_softc*,int /*<<< orphan*/ ) ; 
 struct usb_linux_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc_attached_list ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_linux_cleanup_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
usb_linux_detach(device_t dev)
{
	struct usb_linux_softc *sc = device_get_softc(dev);
	struct usb_driver *udrv = NULL;

	mtx_lock(&Giant);
	if (sc->sc_attached_list.le_prev) {
		LIST_REMOVE(sc, sc_attached_list);
		sc->sc_attached_list.le_prev = NULL;
		udrv = sc->sc_udrv;
		sc->sc_udrv = NULL;
	}
	mtx_unlock(&Giant);

	if (udrv && udrv->disconnect) {
		(udrv->disconnect) (sc->sc_ui);
	}
	/*
	 * Make sure that we free all FreeBSD USB transfers belonging to
	 * this Linux "usb_interface", hence they will most likely not be
	 * needed any more.
	 */
	usb_linux_cleanup_interface(sc->sc_fbsd_udev, sc->sc_ui);
	return (0);
}