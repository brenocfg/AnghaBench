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
struct rl_softc {scalar_t__ suspended; int /*<<< orphan*/  rl_dev; struct ifnet* rl_ifp; } ;
struct ifnet {int if_capabilities; int if_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFCAP_WOL ; 
 int IFF_UP ; 
 int PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 struct rl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  rl_clrwol (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_init_locked (struct rl_softc*) ; 

__attribute__((used)) static int
rl_resume(device_t dev)
{
	struct rl_softc		*sc;
	struct ifnet		*ifp;
	int			pmc;
	uint16_t		pmstat;

	sc = device_get_softc(dev);
	ifp = sc->rl_ifp;

	RL_LOCK(sc);

	if ((ifp->if_capabilities & IFCAP_WOL) != 0 &&
	    pci_find_cap(sc->rl_dev, PCIY_PMG, &pmc) == 0) {
		/* Disable PME and clear PME status. */
		pmstat = pci_read_config(sc->rl_dev,
		    pmc + PCIR_POWER_STATUS, 2);
		if ((pmstat & PCIM_PSTAT_PMEENABLE) != 0) {
			pmstat &= ~PCIM_PSTAT_PMEENABLE;
			pci_write_config(sc->rl_dev,
			    pmc + PCIR_POWER_STATUS, pmstat, 2);
		}
		/*
		 * Clear WOL matching such that normal Rx filtering
		 * wouldn't interfere with WOL patterns.
		 */
		rl_clrwol(sc);
	}

	/* reinitialize interface if necessary */
	if (ifp->if_flags & IFF_UP)
		rl_init_locked(sc);

	sc->suspended = 0;

	RL_UNLOCK(sc);

	return (0);
}