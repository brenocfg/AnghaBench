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
typedef  int /*<<< orphan*/  uint16_t ;
struct jme_softc {struct ifnet* jme_ifp; int /*<<< orphan*/  jme_dev; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  JME_LOCK (struct jme_softc*) ; 
 int /*<<< orphan*/  JME_UNLOCK (struct jme_softc*) ; 
 int /*<<< orphan*/  PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 struct jme_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jme_init_locked (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_phy_up (struct jme_softc*) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
jme_resume(device_t dev)
{
	struct jme_softc *sc;
	struct ifnet *ifp;
	uint16_t pmstat;
	int pmc;

	sc = device_get_softc(dev);

	JME_LOCK(sc);
	if (pci_find_cap(sc->jme_dev, PCIY_PMG, &pmc) == 0) {
		pmstat = pci_read_config(sc->jme_dev,
		    pmc + PCIR_POWER_STATUS, 2);
		/* Disable PME clear PME status. */
		pmstat &= ~PCIM_PSTAT_PMEENABLE;
		pci_write_config(sc->jme_dev,
		    pmc + PCIR_POWER_STATUS, pmstat, 2);
	}
	/* Wakeup PHY. */
	jme_phy_up(sc);
	ifp = sc->jme_ifp;
	if ((ifp->if_flags & IFF_UP) != 0) {
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		jme_init_locked(sc);
	}

	JME_UNLOCK(sc);

	return (0);
}