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
struct mfi_softc {int mfi_flags; int mfi_detaching; int /*<<< orphan*/  mfi_eh; int /*<<< orphan*/  mfi_config_lock; int /*<<< orphan*/  mfi_dev; int /*<<< orphan*/  mfi_io_lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MFI_FLAGS_OPEN ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 struct mfi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_free (struct mfi_softc*) ; 
 int /*<<< orphan*/  mfi_pci_free (struct mfi_softc*) ; 
 int /*<<< orphan*/  mfi_shutdown (struct mfi_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mfi_pci_detach(device_t dev)
{
	struct mfi_softc *sc;
	int error, devcount, i;
	device_t *devlist;

	sc = device_get_softc(dev);

	sx_xlock(&sc->mfi_config_lock);
	mtx_lock(&sc->mfi_io_lock);
	if ((sc->mfi_flags & MFI_FLAGS_OPEN) != 0) {
		mtx_unlock(&sc->mfi_io_lock);
		sx_xunlock(&sc->mfi_config_lock);
		return (EBUSY);
	}
	sc->mfi_detaching = 1;
	mtx_unlock(&sc->mfi_io_lock);

	if ((error = device_get_children(sc->mfi_dev, &devlist, &devcount)) != 0) {
		sx_xunlock(&sc->mfi_config_lock);
		return error;
	}
	for (i = 0; i < devcount; i++)
		device_delete_child(sc->mfi_dev, devlist[i]);
	free(devlist, M_TEMP);
	sx_xunlock(&sc->mfi_config_lock);

	EVENTHANDLER_DEREGISTER(shutdown_final, sc->mfi_eh);

	mfi_shutdown(sc);
	mfi_free(sc);
	mfi_pci_free(sc);
	return (0);
}