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
struct g_keyboard_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_mode; int /*<<< orphan*/  sc_callout; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  G_KEYBOARD_MODE_SILENT ; 
 int /*<<< orphan*/  G_KEYBOARD_N_TRANSFER ; 
 int /*<<< orphan*/  MTX_DEF ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct g_keyboard_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_keyboard_config ; 
 int /*<<< orphan*/  g_keyboard_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_keyboard_timeout_reset (struct g_keyboard_softc*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct g_keyboard_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_keyboard_attach(device_t dev)
{
	struct g_keyboard_softc *sc = device_get_softc(dev);
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	int error;

	DPRINTFN(11, "\n");

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, "g_keyboard", NULL, MTX_DEF);

	usb_callout_init_mtx(&sc->sc_callout, &sc->sc_mtx, 0);

	sc->sc_mode = G_KEYBOARD_MODE_SILENT;

	error = usbd_transfer_setup(uaa->device,
	    &uaa->info.bIfaceIndex, sc->sc_xfer, g_keyboard_config,
	    G_KEYBOARD_N_TRANSFER, sc, &sc->sc_mtx);

	if (error) {
		DPRINTF("error=%s\n", usbd_errstr(error));
		goto detach;
	}
	mtx_lock(&sc->sc_mtx);
	g_keyboard_timeout_reset(sc);
	mtx_unlock(&sc->sc_mtx);

	return (0);			/* success */

detach:
	g_keyboard_detach(dev);

	return (ENXIO);			/* error */
}