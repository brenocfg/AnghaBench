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
struct rl_softc {int rl_flags; int /*<<< orphan*/  rl_dev; int /*<<< orphan*/  rl_cfg5; int /*<<< orphan*/  rl_cfg3; int /*<<< orphan*/  rl_cfg1; struct ifnet* rl_ifp; } ;
struct ifnet {int if_capenable; } ;

/* Variables and functions */
 int CSR_READ_1 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_WOL ; 
 int IFCAP_WOL_MAGIC ; 
 int IFCAP_WOL_MCAST ; 
 int IFCAP_WOL_UCAST ; 
 int PCIM_PSTAT_PME ; 
 int PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 int RL_CFG1_PME ; 
 int RL_CFG3_WOL_LINK ; 
 int RL_CFG3_WOL_MAGIC ; 
 int RL_CFG5_WOL_BCAST ; 
 int RL_CFG5_WOL_LANWAKE ; 
 int RL_CFG5_WOL_MCAST ; 
 int RL_CFG5_WOL_UCAST ; 
 int RL_CMD_RX_ENB ; 
 int /*<<< orphan*/  RL_COMMAND ; 
 int /*<<< orphan*/  RL_EECMD ; 
 int RL_EEMODE_OFF ; 
 int RL_EE_MODE ; 
 int RL_FLAG_8168G_PLUS ; 
 int RL_FLAG_MACSLEEP ; 
 int RL_FLAG_PHYWAKE_PM ; 
 int RL_FLAG_WOLRXENB ; 
 int RL_FLAG_WOL_MANLINK ; 
 int /*<<< orphan*/  RL_GPIO ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_MACDBG ; 
 int /*<<< orphan*/  RL_MISC ; 
 int /*<<< orphan*/  RL_PMCH ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  re_set_linkspeed (struct rl_softc*) ; 
 int /*<<< orphan*/  re_set_rxmode (struct rl_softc*) ; 

__attribute__((used)) static void
re_setwol(struct rl_softc *sc)
{
	struct ifnet		*ifp;
	int			pmc;
	uint16_t		pmstat;
	uint8_t			v;

	RL_LOCK_ASSERT(sc);

	if (pci_find_cap(sc->rl_dev, PCIY_PMG, &pmc) != 0)
		return;

	ifp = sc->rl_ifp;
	/* Put controller into sleep mode. */
	if ((sc->rl_flags & RL_FLAG_MACSLEEP) != 0) {
		if ((CSR_READ_1(sc, RL_MACDBG) & 0x80) == 0x80)
			CSR_WRITE_1(sc, RL_GPIO,
			    CSR_READ_1(sc, RL_GPIO) & ~0x01);
	}
	if ((ifp->if_capenable & IFCAP_WOL) != 0) {
		if ((sc->rl_flags & RL_FLAG_8168G_PLUS) != 0) {
			/* Disable RXDV gate. */
			CSR_WRITE_4(sc, RL_MISC, CSR_READ_4(sc, RL_MISC) &
			    ~0x00080000);
		}
		re_set_rxmode(sc);
		if ((sc->rl_flags & RL_FLAG_WOL_MANLINK) != 0)
			re_set_linkspeed(sc);
		if ((sc->rl_flags & RL_FLAG_WOLRXENB) != 0)
			CSR_WRITE_1(sc, RL_COMMAND, RL_CMD_RX_ENB);
	}
	/* Enable config register write. */
	CSR_WRITE_1(sc, RL_EECMD, RL_EE_MODE);

	/* Enable PME. */
	v = CSR_READ_1(sc, sc->rl_cfg1);
	v &= ~RL_CFG1_PME;
	if ((ifp->if_capenable & IFCAP_WOL) != 0)
		v |= RL_CFG1_PME;
	CSR_WRITE_1(sc, sc->rl_cfg1, v);

	v = CSR_READ_1(sc, sc->rl_cfg3);
	v &= ~(RL_CFG3_WOL_LINK | RL_CFG3_WOL_MAGIC);
	if ((ifp->if_capenable & IFCAP_WOL_MAGIC) != 0)
		v |= RL_CFG3_WOL_MAGIC;
	CSR_WRITE_1(sc, sc->rl_cfg3, v);

	v = CSR_READ_1(sc, sc->rl_cfg5);
	v &= ~(RL_CFG5_WOL_BCAST | RL_CFG5_WOL_MCAST | RL_CFG5_WOL_UCAST |
	    RL_CFG5_WOL_LANWAKE);
	if ((ifp->if_capenable & IFCAP_WOL_UCAST) != 0)
		v |= RL_CFG5_WOL_UCAST;
	if ((ifp->if_capenable & IFCAP_WOL_MCAST) != 0)
		v |= RL_CFG5_WOL_MCAST | RL_CFG5_WOL_BCAST;
	if ((ifp->if_capenable & IFCAP_WOL) != 0)
		v |= RL_CFG5_WOL_LANWAKE;
	CSR_WRITE_1(sc, sc->rl_cfg5, v);

	/* Config register write done. */
	CSR_WRITE_1(sc, RL_EECMD, RL_EEMODE_OFF);

	if ((ifp->if_capenable & IFCAP_WOL) == 0 &&
	    (sc->rl_flags & RL_FLAG_PHYWAKE_PM) != 0)
		CSR_WRITE_1(sc, RL_PMCH, CSR_READ_1(sc, RL_PMCH) & ~0x80);
	/*
	 * It seems that hardware resets its link speed to 100Mbps in
	 * power down mode so switching to 100Mbps in driver is not
	 * needed.
	 */

	/* Request PME if WOL is requested. */
	pmstat = pci_read_config(sc->rl_dev, pmc + PCIR_POWER_STATUS, 2);
	pmstat &= ~(PCIM_PSTAT_PME | PCIM_PSTAT_PMEENABLE);
	if ((ifp->if_capenable & IFCAP_WOL) != 0)
		pmstat |= PCIM_PSTAT_PME | PCIM_PSTAT_PMEENABLE;
	pci_write_config(sc->rl_dev, pmc + PCIR_POWER_STATUS, pmstat, 2);
}