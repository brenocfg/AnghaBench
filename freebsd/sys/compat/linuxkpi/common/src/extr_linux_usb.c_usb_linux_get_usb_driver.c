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
struct usb_linux_softc {struct usb_driver* sc_udrv; } ;
struct usb_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct usb_driver *
usb_linux_get_usb_driver(struct usb_linux_softc *sc)
{
	struct usb_driver *udrv;

	mtx_lock(&Giant);
	udrv = sc->sc_udrv;
	mtx_unlock(&Giant);
	return (udrv);
}