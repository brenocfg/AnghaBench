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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct ste_softc {int /*<<< orphan*/  ste_dev; struct ifnet* ste_ifp; } ;
struct ifnet {int if_capenable; } ;

/* Variables and functions */
 int CSR_READ_1 (struct ste_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct ste_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_WOL_MAGIC ; 
 int PCIM_PSTAT_PME ; 
 int PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 int /*<<< orphan*/  STE_LOCK_ASSERT (struct ste_softc*) ; 
 int STE_WAKEEVENT_LINKEVT_ENB ; 
 int STE_WAKEEVENT_MAGICPKT_ENB ; 
 int STE_WAKEEVENT_WAKEONLAN_ENB ; 
 int STE_WAKEEVENT_WAKEPKT_ENB ; 
 int /*<<< orphan*/  STE_WAKE_EVENT ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static void
ste_setwol(struct ste_softc *sc)
{
	struct ifnet *ifp;
	uint16_t pmstat;
	uint8_t val;
	int pmc;

	STE_LOCK_ASSERT(sc);

	if (pci_find_cap(sc->ste_dev, PCIY_PMG, &pmc) != 0) {
		/* Disable WOL. */
		CSR_READ_1(sc, STE_WAKE_EVENT);
		CSR_WRITE_1(sc, STE_WAKE_EVENT, 0);
		return;
	}

	ifp = sc->ste_ifp;
	val = CSR_READ_1(sc, STE_WAKE_EVENT);
	val &= ~(STE_WAKEEVENT_WAKEPKT_ENB | STE_WAKEEVENT_MAGICPKT_ENB |
	    STE_WAKEEVENT_LINKEVT_ENB | STE_WAKEEVENT_WAKEONLAN_ENB);
	if ((ifp->if_capenable & IFCAP_WOL_MAGIC) != 0)
		val |= STE_WAKEEVENT_MAGICPKT_ENB | STE_WAKEEVENT_WAKEONLAN_ENB;
	CSR_WRITE_1(sc, STE_WAKE_EVENT, val);
	/* Request PME. */
	pmstat = pci_read_config(sc->ste_dev, pmc + PCIR_POWER_STATUS, 2);
	pmstat &= ~(PCIM_PSTAT_PME | PCIM_PSTAT_PMEENABLE);
	if ((ifp->if_capenable & IFCAP_WOL_MAGIC) != 0)
		pmstat |= PCIM_PSTAT_PME | PCIM_PSTAT_PMEENABLE;
	pci_write_config(sc->ste_dev, pmc + PCIR_POWER_STATUS, pmstat, 2);
}