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
struct cfumass_softc {scalar_t__ sc_ctl_initid; int /*<<< orphan*/  sc_queued; int /*<<< orphan*/ * sc_xfer; void* sc_csw; void* sc_cbw; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFUMASS_DEBUG (struct cfumass_softc*,char*) ; 
 int /*<<< orphan*/  CFUMASS_LOCK (struct cfumass_softc*) ; 
 size_t CFUMASS_T_COMMAND ; 
 int /*<<< orphan*/  CFUMASS_T_MAX ; 
 size_t CFUMASS_T_STATUS ; 
 int /*<<< orphan*/  CFUMASS_UNLOCK (struct cfumass_softc*) ; 
 int /*<<< orphan*/  CFUMASS_WARN (struct cfumass_softc*,char*,scalar_t__) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  USB_POWER_MODE_SAVE ; 
 int /*<<< orphan*/  cfumass_config ; 
 int /*<<< orphan*/  cfumass_port ; 
 int /*<<< orphan*/  cfumass_refcount ; 
 int /*<<< orphan*/  cfumass_transfer_start (struct cfumass_softc*,size_t) ; 
 scalar_t__ ctl_add_initiator (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct cfumass_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 
 scalar_t__ usbd_errstr (int) ; 
 int /*<<< orphan*/  usbd_set_power_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfumass_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* usbd_xfer_get_frame_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cfumass_attach(device_t dev)
{
	struct cfumass_softc *sc;
	struct usb_attach_arg *uaa;
	int error;

	sc = device_get_softc(dev);
	uaa = device_get_ivars(dev);

	sc->sc_dev = dev;
	sc->sc_udev = uaa->device;

	CFUMASS_DEBUG(sc, "go");

	usbd_set_power_mode(uaa->device, USB_POWER_MODE_SAVE);
	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, "cfumass", NULL, MTX_DEF);
	refcount_acquire(&cfumass_refcount);

	error = usbd_transfer_setup(uaa->device,
	    &uaa->info.bIfaceIndex, sc->sc_xfer, cfumass_config,
	    CFUMASS_T_MAX, sc, &sc->sc_mtx);
	if (error != 0) {
		CFUMASS_WARN(sc, "usbd_transfer_setup() failed: %s",
		    usbd_errstr(error));
		refcount_release(&cfumass_refcount);
		return (ENXIO);
	}

	sc->sc_cbw =
	    usbd_xfer_get_frame_buffer(sc->sc_xfer[CFUMASS_T_COMMAND], 0);
	sc->sc_csw =
	    usbd_xfer_get_frame_buffer(sc->sc_xfer[CFUMASS_T_STATUS], 0);

	sc->sc_ctl_initid = ctl_add_initiator(&cfumass_port, -1, 0, NULL);
	if (sc->sc_ctl_initid < 0) {
		CFUMASS_WARN(sc, "ctl_add_initiator() failed with error %d",
		    sc->sc_ctl_initid);
		usbd_transfer_unsetup(sc->sc_xfer, CFUMASS_T_MAX);
		refcount_release(&cfumass_refcount);
		return (ENXIO);
	}

	refcount_init(&sc->sc_queued, 0);

	CFUMASS_LOCK(sc);
	cfumass_transfer_start(sc, CFUMASS_T_COMMAND);
	CFUMASS_UNLOCK(sc);

	return (0);
}