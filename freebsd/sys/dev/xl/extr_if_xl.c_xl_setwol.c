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
typedef  int /*<<< orphan*/  u_int16_t ;
struct xl_softc {int xl_flags; scalar_t__ xl_pmcap; int /*<<< orphan*/  xl_dev; struct ifnet* xl_ifp; } ;
struct ifnet {int if_capenable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_2 (struct xl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct xl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFCAP_WOL_MAGIC ; 
 int /*<<< orphan*/  PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int /*<<< orphan*/  XL_BM_PME_MAGIC ; 
 int /*<<< orphan*/  XL_CMD_RX_ENABLE ; 
 int /*<<< orphan*/  XL_COMMAND ; 
 int XL_FLAG_WOL ; 
 int /*<<< orphan*/  XL_SEL_WIN (int) ; 
 int /*<<< orphan*/  XL_W7_BM_PME ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xl_setwol(struct xl_softc *sc)
{
	struct ifnet		*ifp;
	u_int16_t		cfg, pmstat;

	if ((sc->xl_flags & XL_FLAG_WOL) == 0)
		return;

	ifp = sc->xl_ifp;
	XL_SEL_WIN(7);
	/* Clear any pending PME events. */
	CSR_READ_2(sc, XL_W7_BM_PME);
	cfg = 0;
	if ((ifp->if_capenable & IFCAP_WOL_MAGIC) != 0)
		cfg |= XL_BM_PME_MAGIC;
	CSR_WRITE_2(sc, XL_W7_BM_PME, cfg);
	/* Enable RX. */
	if ((ifp->if_capenable & IFCAP_WOL_MAGIC) != 0)
		CSR_WRITE_2(sc, XL_COMMAND, XL_CMD_RX_ENABLE);
	/* Request PME. */
	pmstat = pci_read_config(sc->xl_dev,
	    sc->xl_pmcap + PCIR_POWER_STATUS, 2);
	if ((ifp->if_capenable & IFCAP_WOL_MAGIC) != 0)
		pmstat |= PCIM_PSTAT_PMEENABLE;
	else
		pmstat &= ~PCIM_PSTAT_PMEENABLE;
	pci_write_config(sc->xl_dev,
	    sc->xl_pmcap + PCIR_POWER_STATUS, pmstat, 2);
}