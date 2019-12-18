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
struct udl_softc {int sc_gone; int /*<<< orphan*/  sc_fb_copy; int /*<<< orphan*/  sc_fb_size; int /*<<< orphan*/  sc_fb_addr; int /*<<< orphan*/  sc_cv; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_callout; int /*<<< orphan*/  sc_xfer; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_USB_DL ; 
 int /*<<< orphan*/  UDL_LOCK (struct udl_softc*) ; 
 int /*<<< orphan*/  UDL_N_TRANSFER ; 
 int /*<<< orphan*/  UDL_UNLOCK (struct udl_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct udl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udl_buffer_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udl_detach(device_t dev)
{
	struct udl_softc *sc = device_get_softc(dev);

	/* delete all child devices */
	device_delete_children(dev);

	UDL_LOCK(sc);
	sc->sc_gone = 1;
	callout_stop(&sc->sc_callout);
	UDL_UNLOCK(sc);

	usbd_transfer_unsetup(sc->sc_xfer, UDL_N_TRANSFER);

	callout_drain(&sc->sc_callout);

	mtx_destroy(&sc->sc_mtx);
	cv_destroy(&sc->sc_cv);

	/* put main framebuffer into a recycle list, if any */
	udl_buffer_free(sc->sc_fb_addr, sc->sc_fb_size);

	/* free shadow framebuffer memory, if any */
	free(sc->sc_fb_copy, M_USB_DL);

	return (0);
}