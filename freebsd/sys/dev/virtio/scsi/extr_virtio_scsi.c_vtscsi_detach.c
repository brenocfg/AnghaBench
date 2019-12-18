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
struct vtscsi_softc {int /*<<< orphan*/ * vtscsi_sglist; int /*<<< orphan*/  vtscsi_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VTSCSI_FLAG_DETACH ; 
 int /*<<< orphan*/  VTSCSI_LOCK (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  VTSCSI_LOCK_DESTROY (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  VTSCSI_UNLOCK (struct vtscsi_softc*) ; 
 struct vtscsi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sglist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtscsi_complete_vqs (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_drain_vqs (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_free_cam (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_free_requests (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_stop (struct vtscsi_softc*) ; 

__attribute__((used)) static int
vtscsi_detach(device_t dev)
{
	struct vtscsi_softc *sc;

	sc = device_get_softc(dev);

	VTSCSI_LOCK(sc);
	sc->vtscsi_flags |= VTSCSI_FLAG_DETACH;
	if (device_is_attached(dev))
		vtscsi_stop(sc);
	VTSCSI_UNLOCK(sc);

	vtscsi_complete_vqs(sc);
	vtscsi_drain_vqs(sc);

	vtscsi_free_cam(sc);
	vtscsi_free_requests(sc);

	if (sc->vtscsi_sglist != NULL) {
		sglist_free(sc->vtscsi_sglist);
		sc->vtscsi_sglist = NULL;
	}

	VTSCSI_LOCK_DESTROY(sc);

	return (0);
}