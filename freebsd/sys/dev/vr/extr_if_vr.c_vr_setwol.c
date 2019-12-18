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
struct vr_softc {scalar_t__ vr_revid; int /*<<< orphan*/  vr_dev; struct ifnet* vr_ifp; } ;
struct ifnet {int if_capenable; } ;

/* Variables and functions */
 int CSR_READ_1 (struct vr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_WOL ; 
 int IFCAP_WOL_MAGIC ; 
 int IFCAP_WOL_UCAST ; 
 int PCIM_PSTAT_PME ; 
 int PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 scalar_t__ REV_ID_VT6102_A ; 
 scalar_t__ REV_ID_VT6105_B0 ; 
 int /*<<< orphan*/  VR_LOCK_ASSERT (struct vr_softc*) ; 
 int /*<<< orphan*/  VR_PWRCFG_CLR ; 
 int /*<<< orphan*/  VR_PWRCFG_SET ; 
 int VR_PWRCFG_WOLEN ; 
 int /*<<< orphan*/  VR_PWRCSR1_CLR ; 
 int /*<<< orphan*/  VR_PWRCSR_CLR ; 
 int /*<<< orphan*/  VR_STICKHW ; 
 int VR_STICKHW_DS0 ; 
 int VR_STICKHW_DS1 ; 
 int VR_STICKHW_WOL_ENB ; 
 int /*<<< orphan*/  VR_TESTREG_CLR ; 
 int /*<<< orphan*/  VR_WOLCFG_CLR ; 
 int VR_WOLCFG_PATTERN_PAGE ; 
 int VR_WOLCFG_SAB ; 
 int VR_WOLCFG_SAM ; 
 int /*<<< orphan*/  VR_WOLCFG_SET ; 
 int /*<<< orphan*/  VR_WOLCR_CLR ; 
 int VR_WOLCR_MAGIC ; 
 int /*<<< orphan*/  VR_WOLCR_SET ; 
 int VR_WOLCR_UCAST ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static void
vr_setwol(struct vr_softc *sc)
{
	struct ifnet		*ifp;
	int			pmc;
	uint16_t		pmstat;
	uint8_t			v;

	VR_LOCK_ASSERT(sc);

	if (sc->vr_revid < REV_ID_VT6102_A ||
	    pci_find_cap(sc->vr_dev, PCIY_PMG, &pmc) != 0)
		return;

	ifp = sc->vr_ifp;

	/* Clear WOL configuration. */
	CSR_WRITE_1(sc, VR_WOLCR_CLR, 0xFF);
	CSR_WRITE_1(sc, VR_WOLCFG_CLR, VR_WOLCFG_SAB | VR_WOLCFG_SAM);
	CSR_WRITE_1(sc, VR_PWRCSR_CLR, 0xFF);
	CSR_WRITE_1(sc, VR_PWRCFG_CLR, VR_PWRCFG_WOLEN);
	if (sc->vr_revid > REV_ID_VT6105_B0) {
		/* Newer Rhine III supports two additional patterns. */
		CSR_WRITE_1(sc, VR_WOLCFG_CLR, VR_WOLCFG_PATTERN_PAGE);
		CSR_WRITE_1(sc, VR_TESTREG_CLR, 3);
		CSR_WRITE_1(sc, VR_PWRCSR1_CLR, 3);
	}
	if ((ifp->if_capenable & IFCAP_WOL_UCAST) != 0)
		CSR_WRITE_1(sc, VR_WOLCR_SET, VR_WOLCR_UCAST);
	if ((ifp->if_capenable & IFCAP_WOL_MAGIC) != 0)
		CSR_WRITE_1(sc, VR_WOLCR_SET, VR_WOLCR_MAGIC);
	/*
	 * It seems that multicast wakeup frames require programming pattern
	 * registers and valid CRC as well as pattern mask for each pattern.
	 * While it's possible to setup such a pattern it would complicate
	 * WOL configuration so ignore multicast wakeup frames.
	 */
	if ((ifp->if_capenable & IFCAP_WOL) != 0) {
		CSR_WRITE_1(sc, VR_WOLCFG_SET, VR_WOLCFG_SAB | VR_WOLCFG_SAM);
		v = CSR_READ_1(sc, VR_STICKHW);
		CSR_WRITE_1(sc, VR_STICKHW, v | VR_STICKHW_WOL_ENB);
		CSR_WRITE_1(sc, VR_PWRCFG_SET, VR_PWRCFG_WOLEN);
	}

	/* Put hardware into sleep. */
	v = CSR_READ_1(sc, VR_STICKHW);
	v |= VR_STICKHW_DS0 | VR_STICKHW_DS1;
	CSR_WRITE_1(sc, VR_STICKHW, v);

	/* Request PME if WOL is requested. */
	pmstat = pci_read_config(sc->vr_dev, pmc + PCIR_POWER_STATUS, 2);
	pmstat &= ~(PCIM_PSTAT_PME | PCIM_PSTAT_PMEENABLE);
	if ((ifp->if_capenable & IFCAP_WOL) != 0)
		pmstat |= PCIM_PSTAT_PME | PCIM_PSTAT_PMEENABLE;
	pci_write_config(sc->vr_dev, pmc + PCIR_POWER_STATUS, pmstat, 2);
}