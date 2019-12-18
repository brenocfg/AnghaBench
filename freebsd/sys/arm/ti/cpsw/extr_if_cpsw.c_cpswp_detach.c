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
struct cpswp_softc {int /*<<< orphan*/  lock; int /*<<< orphan*/  ifp; int /*<<< orphan*/  mii_callout; int /*<<< orphan*/  swsc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CPSW_PORT_LOCK (struct cpswp_softc*) ; 
 int /*<<< orphan*/  CPSW_PORT_UNLOCK (struct cpswp_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpswp_stop_locked (struct cpswp_softc*) ; 
 struct cpswp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cpswp_detach(device_t dev)
{
	struct cpswp_softc *sc;

	sc = device_get_softc(dev);
	CPSW_DEBUGF(sc->swsc, (""));
	if (device_is_attached(dev)) {
		ether_ifdetach(sc->ifp);
		CPSW_PORT_LOCK(sc);
		cpswp_stop_locked(sc);
		CPSW_PORT_UNLOCK(sc);
		callout_drain(&sc->mii_callout);
	}

	bus_generic_detach(dev);

	if_free(sc->ifp);
	mtx_destroy(&sc->lock);

	return (0);
}