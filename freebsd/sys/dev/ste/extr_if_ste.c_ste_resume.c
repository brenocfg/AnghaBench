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
struct ste_softc {struct ifnet* ste_ifp; int /*<<< orphan*/  ste_dev; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 int /*<<< orphan*/  STE_LOCK (struct ste_softc*) ; 
 int /*<<< orphan*/  STE_UNLOCK (struct ste_softc*) ; 
 struct ste_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  ste_init_locked (struct ste_softc*) ; 

__attribute__((used)) static int
ste_resume(device_t dev)
{
	struct ste_softc *sc;
	struct ifnet *ifp;
	int pmc;
	uint16_t pmstat;

	sc = device_get_softc(dev);
	STE_LOCK(sc);
	if (pci_find_cap(sc->ste_dev, PCIY_PMG, &pmc) == 0) {
		/* Disable PME and clear PME status. */
		pmstat = pci_read_config(sc->ste_dev,
		    pmc + PCIR_POWER_STATUS, 2);
		if ((pmstat & PCIM_PSTAT_PMEENABLE) != 0) {
			pmstat &= ~PCIM_PSTAT_PMEENABLE;
			pci_write_config(sc->ste_dev,
			    pmc + PCIR_POWER_STATUS, pmstat, 2);
		}
	}
	ifp = sc->ste_ifp;
	if ((ifp->if_flags & IFF_UP) != 0) {
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		ste_init_locked(sc);
	}
	STE_UNLOCK(sc);

	return (0);
}