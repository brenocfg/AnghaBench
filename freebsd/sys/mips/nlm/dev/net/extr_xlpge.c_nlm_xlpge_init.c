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
struct nlm_xlpge_softc {int /*<<< orphan*/  xlpge_callout; scalar_t__ mii_bus; struct ifnet* xlpge_if; } ;
struct mii_data {int dummy; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlm_xlpge_softc*) ; 
 struct mii_data* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 int /*<<< orphan*/  nlm_mii_pollstat ; 
 int /*<<< orphan*/  nlm_xlpge_gmac_config_speed (struct nlm_xlpge_softc*) ; 
 int /*<<< orphan*/  nlm_xlpge_port_enable (struct nlm_xlpge_softc*) ; 

__attribute__((used)) static void
nlm_xlpge_init(void *addr)
{
	struct nlm_xlpge_softc *sc;
	struct ifnet   *ifp;
	struct mii_data *mii = NULL;

	sc = (struct nlm_xlpge_softc *)addr;
	ifp = sc->xlpge_if;

	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return;

	if (sc->mii_bus) {
		mii = device_get_softc(sc->mii_bus);
		mii_mediachg(mii);
	}

	nlm_xlpge_gmac_config_speed(sc);
	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
	nlm_xlpge_port_enable(sc);

	/* start the callout */
	callout_reset(&sc->xlpge_callout, hz, nlm_mii_pollstat, sc);
}