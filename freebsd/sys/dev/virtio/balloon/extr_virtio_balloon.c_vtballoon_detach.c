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
struct vtballoon_softc {int /*<<< orphan*/ * vtballoon_page_frames; int /*<<< orphan*/ * vtballoon_td; int /*<<< orphan*/  vtballoon_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  VTBALLOON_FLAG_DETACH ; 
 int /*<<< orphan*/  VTBALLOON_LOCK (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  VTBALLOON_LOCK_DESTROY (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  VTBALLOON_MTX (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  VTBALLOON_UNLOCK (struct vtballoon_softc*) ; 
 struct vtballoon_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtballoon_pop (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  vtballoon_stop (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  wakeup_one (struct vtballoon_softc*) ; 

__attribute__((used)) static int
vtballoon_detach(device_t dev)
{
	struct vtballoon_softc *sc;

	sc = device_get_softc(dev);

	if (sc->vtballoon_td != NULL) {
		VTBALLOON_LOCK(sc);
		sc->vtballoon_flags |= VTBALLOON_FLAG_DETACH;
		wakeup_one(sc);
		msleep(sc->vtballoon_td, VTBALLOON_MTX(sc), 0, "vtbdth", 0);
		VTBALLOON_UNLOCK(sc);

		sc->vtballoon_td = NULL;
	}

	if (device_is_attached(dev)) {
		vtballoon_pop(sc);
		vtballoon_stop(sc);
	}

	if (sc->vtballoon_page_frames != NULL) {
		free(sc->vtballoon_page_frames, M_DEVBUF);
		sc->vtballoon_page_frames = NULL;
	}

	VTBALLOON_LOCK_DESTROY(sc);

	return (0);
}