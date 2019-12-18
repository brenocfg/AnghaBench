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
struct ustorage_fs_softc {size_t sc_last_xfer_index; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_drain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ustorage_fs_transfer_stop(struct ustorage_fs_softc *sc)
{
	usbd_transfer_stop(sc->sc_xfer[sc->sc_last_xfer_index]);
	mtx_unlock(&sc->sc_mtx);
	usbd_transfer_drain(sc->sc_xfer[sc->sc_last_xfer_index]);
	mtx_lock(&sc->sc_mtx);
}