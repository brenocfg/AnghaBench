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
struct TYPE_2__ {int /*<<< orphan*/  bIfaceIndex; } ;
struct usb_attach_arg {TYPE_1__ info; int /*<<< orphan*/  device; } ;
struct ufm_softc {int /*<<< orphan*/  sc_fifo; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_name; int /*<<< orphan*/  sc_unit; int /*<<< orphan*/  sc_udev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 int /*<<< orphan*/  UID_ROOT ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ufm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  ufm_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufm_fifo_methods ; 
 int usb_fifo_attach (int /*<<< orphan*/ ,struct ufm_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ufm_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct ufm_softc *sc = device_get_softc(dev);
	int error;

	sc->sc_udev = uaa->device;
	sc->sc_unit = device_get_unit(dev);

	snprintf(sc->sc_name, sizeof(sc->sc_name), "%s",
	    device_get_nameunit(dev));

	mtx_init(&sc->sc_mtx, "ufm lock", NULL, MTX_DEF | MTX_RECURSE);

	device_set_usb_desc(dev);

	error = usb_fifo_attach(uaa->device, sc, &sc->sc_mtx,
	    &ufm_fifo_methods, &sc->sc_fifo,
	    device_get_unit(dev), -1, uaa->info.bIfaceIndex,
	    UID_ROOT, GID_OPERATOR, 0644);
	if (error) {
		goto detach;
	}
	return (0);			/* success */

detach:
	ufm_detach(dev);
	return (ENXIO);
}