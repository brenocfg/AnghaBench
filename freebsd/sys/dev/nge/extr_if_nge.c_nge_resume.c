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
struct nge_softc {int /*<<< orphan*/  nge_flags; int /*<<< orphan*/  nge_dev; struct ifnet* nge_ifp; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NGE_FLAG_SUSPENDED ; 
 int /*<<< orphan*/  NGE_LOCK (struct nge_softc*) ; 
 int /*<<< orphan*/  NGE_UNLOCK (struct nge_softc*) ; 
 int PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 struct nge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nge_init_locked (struct nge_softc*) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int
nge_resume(device_t dev)
{
	struct nge_softc *sc;
	struct ifnet *ifp;
	uint16_t pmstat;
	int pmc;

	sc = device_get_softc(dev);

	NGE_LOCK(sc);
	ifp = sc->nge_ifp;
	if (pci_find_cap(sc->nge_dev, PCIY_PMG, &pmc) == 0) {
		/* Disable PME and clear PME status. */
		pmstat = pci_read_config(sc->nge_dev,
		    pmc + PCIR_POWER_STATUS, 2);
		if ((pmstat & PCIM_PSTAT_PMEENABLE) != 0) {
			pmstat &= ~PCIM_PSTAT_PMEENABLE;
			pci_write_config(sc->nge_dev,
			    pmc + PCIR_POWER_STATUS, pmstat, 2);
		}
	}
	if (ifp->if_flags & IFF_UP) {
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		nge_init_locked(sc);
	}

	sc->nge_flags &= ~NGE_FLAG_SUSPENDED;
	NGE_UNLOCK(sc);

	return (0);
}