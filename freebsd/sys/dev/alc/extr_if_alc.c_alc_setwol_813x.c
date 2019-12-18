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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ifnet {int if_capenable; } ;
struct alc_softc {int alc_flags; scalar_t__ alc_pmcap; int /*<<< orphan*/  alc_dev; struct ifnet* alc_ifp; } ;

/* Variables and functions */
 int ALC_FLAG_FASTETHER ; 
 int ALC_FLAG_PM ; 
 int /*<<< orphan*/  ALC_LOCK_ASSERT (struct alc_softc*) ; 
 int /*<<< orphan*/  ALC_MAC_CFG ; 
 int /*<<< orphan*/  ALC_MASTER_CFG ; 
 int /*<<< orphan*/  ALC_PCIE_PHYMISC ; 
 int /*<<< orphan*/  ALC_WOL_CFG ; 
 int CSR_READ_4 (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_WOL ; 
 int IFCAP_WOL_MAGIC ; 
 int IFCAP_WOL_MCAST ; 
 int MAC_CFG_ALLMULTI ; 
 int MAC_CFG_BCAST ; 
 int MAC_CFG_DBG ; 
 int MAC_CFG_PROMISC ; 
 int MAC_CFG_RX_ENB ; 
 int MASTER_CLK_SEL_DIS ; 
 int PCIE_PHYMISC_FORCE_RCV_DET ; 
 int PCIM_PSTAT_PME ; 
 int PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int WOL_CFG_MAGIC ; 
 int WOL_CFG_MAGIC_ENB ; 
 int /*<<< orphan*/  alc_disable_l0s_l1 (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_phy_down (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_setlinkspeed (struct alc_softc*) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static void
alc_setwol_813x(struct alc_softc *sc)
{
	struct ifnet *ifp;
	uint32_t reg, pmcs;
	uint16_t pmstat;

	ALC_LOCK_ASSERT(sc);

	alc_disable_l0s_l1(sc);
	ifp = sc->alc_ifp;
	if ((sc->alc_flags & ALC_FLAG_PM) == 0) {
		/* Disable WOL. */
		CSR_WRITE_4(sc, ALC_WOL_CFG, 0);
		reg = CSR_READ_4(sc, ALC_PCIE_PHYMISC);
		reg |= PCIE_PHYMISC_FORCE_RCV_DET;
		CSR_WRITE_4(sc, ALC_PCIE_PHYMISC, reg);
		/* Force PHY power down. */
		alc_phy_down(sc);
		CSR_WRITE_4(sc, ALC_MASTER_CFG,
		    CSR_READ_4(sc, ALC_MASTER_CFG) | MASTER_CLK_SEL_DIS);
		return;
	}

	if ((ifp->if_capenable & IFCAP_WOL) != 0) {
		if ((sc->alc_flags & ALC_FLAG_FASTETHER) == 0)
			alc_setlinkspeed(sc);
		CSR_WRITE_4(sc, ALC_MASTER_CFG,
		    CSR_READ_4(sc, ALC_MASTER_CFG) & ~MASTER_CLK_SEL_DIS);
	}

	pmcs = 0;
	if ((ifp->if_capenable & IFCAP_WOL_MAGIC) != 0)
		pmcs |= WOL_CFG_MAGIC | WOL_CFG_MAGIC_ENB;
	CSR_WRITE_4(sc, ALC_WOL_CFG, pmcs);
	reg = CSR_READ_4(sc, ALC_MAC_CFG);
	reg &= ~(MAC_CFG_DBG | MAC_CFG_PROMISC | MAC_CFG_ALLMULTI |
	    MAC_CFG_BCAST);
	if ((ifp->if_capenable & IFCAP_WOL_MCAST) != 0)
		reg |= MAC_CFG_ALLMULTI | MAC_CFG_BCAST;
	if ((ifp->if_capenable & IFCAP_WOL) != 0)
		reg |= MAC_CFG_RX_ENB;
	CSR_WRITE_4(sc, ALC_MAC_CFG, reg);

	reg = CSR_READ_4(sc, ALC_PCIE_PHYMISC);
	reg |= PCIE_PHYMISC_FORCE_RCV_DET;
	CSR_WRITE_4(sc, ALC_PCIE_PHYMISC, reg);
	if ((ifp->if_capenable & IFCAP_WOL) == 0) {
		/* WOL disabled, PHY power down. */
		alc_phy_down(sc);
		CSR_WRITE_4(sc, ALC_MASTER_CFG,
		    CSR_READ_4(sc, ALC_MASTER_CFG) | MASTER_CLK_SEL_DIS);
	}
	/* Request PME. */
	pmstat = pci_read_config(sc->alc_dev,
	    sc->alc_pmcap + PCIR_POWER_STATUS, 2);
	pmstat &= ~(PCIM_PSTAT_PME | PCIM_PSTAT_PMEENABLE);
	if ((ifp->if_capenable & IFCAP_WOL) != 0)
		pmstat |= PCIM_PSTAT_PME | PCIM_PSTAT_PMEENABLE;
	pci_write_config(sc->alc_dev,
	    sc->alc_pmcap + PCIR_POWER_STATUS, pmstat, 2);
}