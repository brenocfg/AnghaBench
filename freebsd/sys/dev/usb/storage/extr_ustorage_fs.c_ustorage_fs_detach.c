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
struct ustorage_fs_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  USTORAGE_FS_T_BBB_MAX ; 
 struct ustorage_fs_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ustorage_fs_detach(device_t dev)
{
	struct ustorage_fs_softc *sc = device_get_softc(dev);

	/* teardown our statemachine */

	usbd_transfer_unsetup(sc->sc_xfer, USTORAGE_FS_T_BBB_MAX);

	mtx_destroy(&sc->sc_mtx);

	return (0);			/* success */
}