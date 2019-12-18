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
typedef  int uint16_t ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_drv_flags; } ;
struct alc_softc {int alc_flags; struct ifnet* alc_ifp; scalar_t__ alc_pmcap; int /*<<< orphan*/  alc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ALC_FLAG_PM ; 
 int /*<<< orphan*/  ALC_LOCK (struct alc_softc*) ; 
 int /*<<< orphan*/  ALC_UNLOCK (struct alc_softc*) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int /*<<< orphan*/  alc_init_locked (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_phy_reset (struct alc_softc*) ; 
 struct alc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int
alc_resume(device_t dev)
{
	struct alc_softc *sc;
	struct ifnet *ifp;
	uint16_t pmstat;

	sc = device_get_softc(dev);

	ALC_LOCK(sc);
	if ((sc->alc_flags & ALC_FLAG_PM) != 0) {
		/* Disable PME and clear PME status. */
		pmstat = pci_read_config(sc->alc_dev,
		    sc->alc_pmcap + PCIR_POWER_STATUS, 2);
		if ((pmstat & PCIM_PSTAT_PMEENABLE) != 0) {
			pmstat &= ~PCIM_PSTAT_PMEENABLE;
			pci_write_config(sc->alc_dev,
			    sc->alc_pmcap + PCIR_POWER_STATUS, pmstat, 2);
		}
	}
	/* Reset PHY. */
	alc_phy_reset(sc);
	ifp = sc->alc_ifp;
	if ((ifp->if_flags & IFF_UP) != 0) {
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		alc_init_locked(sc);
	}
	ALC_UNLOCK(sc);

	return (0);
}