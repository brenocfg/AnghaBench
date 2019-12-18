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
struct TYPE_2__ {int /*<<< orphan*/  bIfaceIndex; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_attach_arg {TYPE_1__ info; int /*<<< orphan*/  device; } ;
struct uep_softc {scalar_t__ buf_len; int /*<<< orphan*/  fifo; int /*<<< orphan*/  mtx; int /*<<< orphan*/  evdev; int /*<<< orphan*/  xfer; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_USB ; 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_SYN ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int /*<<< orphan*/  INPUT_PROP_DIRECT ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  UEP_MAX_X ; 
 int /*<<< orphan*/  UEP_MAX_Y ; 
 int /*<<< orphan*/  UEP_N_TRANSFER ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct uep_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_alloc () ; 
 int evdev_register_mtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evdev_set_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_set_methods (int /*<<< orphan*/ ,struct uep_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evdev_set_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_set_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_set_serial (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uep_config ; 
 int /*<<< orphan*/  uep_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uep_evdev_methods ; 
 int /*<<< orphan*/  uep_fifo_methods ; 
 int usb_fifo_attach (int /*<<< orphan*/ ,struct uep_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_get_serial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uep_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uep_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct uep_softc *sc = device_get_softc(dev);
	int error;

	device_set_usb_desc(dev);

	mtx_init(&sc->mtx, "uep lock", NULL, MTX_DEF);

	error = usbd_transfer_setup(uaa->device, &uaa->info.bIfaceIndex,
	    sc->xfer, uep_config, UEP_N_TRANSFER, sc, &sc->mtx);

	if (error) {
		DPRINTF("usbd_transfer_setup error=%s\n", usbd_errstr(error));
		goto detach;
	}

#ifdef EVDEV_SUPPORT
	sc->evdev = evdev_alloc();
	evdev_set_name(sc->evdev, device_get_desc(dev));
	evdev_set_phys(sc->evdev, device_get_nameunit(dev));
	evdev_set_id(sc->evdev, BUS_USB, uaa->info.idVendor,
	    uaa->info.idProduct, 0);
	evdev_set_serial(sc->evdev, usb_get_serial(uaa->device));
	evdev_set_methods(sc->evdev, sc, &uep_evdev_methods);
	evdev_support_prop(sc->evdev, INPUT_PROP_DIRECT);
	evdev_support_event(sc->evdev, EV_SYN);
	evdev_support_event(sc->evdev, EV_ABS);
	evdev_support_event(sc->evdev, EV_KEY);
	evdev_support_key(sc->evdev, BTN_TOUCH);
	evdev_support_abs(sc->evdev, ABS_X, 0, 0, UEP_MAX_X, 0, 0, 0);
	evdev_support_abs(sc->evdev, ABS_Y, 0, 0, UEP_MAX_Y, 0, 0, 0);

	error = evdev_register_mtx(sc->evdev, &sc->mtx);
	if (error) {
		DPRINTF("evdev_register_mtx error=%s\n", usbd_errstr(error));
		goto detach;
	}
#else /* !EVDEV_SUPPORT */
	error = usb_fifo_attach(uaa->device, sc, &sc->mtx, &uep_fifo_methods,
	    &sc->fifo, device_get_unit(dev), -1, uaa->info.bIfaceIndex,
	    UID_ROOT, GID_OPERATOR, 0644);

        if (error) {
		DPRINTF("usb_fifo_attach error=%s\n", usbd_errstr(error));
                goto detach;
        }
#endif /* !EVDEV_SUPPORT */

	sc->buf_len = 0;

	return (0);	

detach:
	uep_detach(dev);

	return (ENOMEM); /* XXX */
}