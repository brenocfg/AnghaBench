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
struct vtnet_softc {int /*<<< orphan*/  vtnet_tick_ch; struct ifnet* vtnet_ifp; int /*<<< orphan*/  vtnet_dev; } ;
struct ifnet {int if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  VTNET_CORE_LOCK_ASSERT (struct vtnet_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vtnet_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  virtio_reinit_complete (int /*<<< orphan*/ ) ; 
 scalar_t__ vtnet_reinit (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_stop (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_tick ; 
 int /*<<< orphan*/  vtnet_update_link_status (struct vtnet_softc*) ; 
 scalar_t__ vtnet_virtio_reinit (struct vtnet_softc*) ; 

__attribute__((used)) static void
vtnet_init_locked(struct vtnet_softc *sc)
{
	device_t dev;
	struct ifnet *ifp;

	dev = sc->vtnet_dev;
	ifp = sc->vtnet_ifp;

	VTNET_CORE_LOCK_ASSERT(sc);

	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return;

	vtnet_stop(sc);

	/* Reinitialize with the host. */
	if (vtnet_virtio_reinit(sc) != 0)
		goto fail;

	if (vtnet_reinit(sc) != 0)
		goto fail;

	virtio_reinit_complete(dev);

	vtnet_update_link_status(sc);
	callout_reset(&sc->vtnet_tick_ch, hz, vtnet_tick, sc);

	return;

fail:
	vtnet_stop(sc);
}