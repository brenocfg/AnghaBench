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
struct vtblk_softc {int /*<<< orphan*/ * vtblk_sglist; int /*<<< orphan*/ * vtblk_disk; int /*<<< orphan*/  vtblk_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VTBLK_FLAG_DETACH ; 
 int /*<<< orphan*/  VTBLK_LOCK (struct vtblk_softc*) ; 
 int /*<<< orphan*/  VTBLK_LOCK_DESTROY (struct vtblk_softc*) ; 
 int /*<<< orphan*/  VTBLK_UNLOCK (struct vtblk_softc*) ; 
 struct vtblk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sglist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtblk_drain (struct vtblk_softc*) ; 
 int /*<<< orphan*/  vtblk_stop (struct vtblk_softc*) ; 

__attribute__((used)) static int
vtblk_detach(device_t dev)
{
	struct vtblk_softc *sc;

	sc = device_get_softc(dev);

	VTBLK_LOCK(sc);
	sc->vtblk_flags |= VTBLK_FLAG_DETACH;
	if (device_is_attached(dev))
		vtblk_stop(sc);
	VTBLK_UNLOCK(sc);

	vtblk_drain(sc);

	if (sc->vtblk_disk != NULL) {
		disk_destroy(sc->vtblk_disk);
		sc->vtblk_disk = NULL;
	}

	if (sc->vtblk_sglist != NULL) {
		sglist_free(sc->vtblk_sglist);
		sc->vtblk_sglist = NULL;
	}

	VTBLK_LOCK_DESTROY(sc);

	return (0);
}