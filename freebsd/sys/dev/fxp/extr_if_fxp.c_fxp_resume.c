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
struct fxp_softc {int flags; scalar_t__ suspended; int /*<<< orphan*/  dev; int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_1 (struct fxp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct fxp_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct fxp_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  FXP_CSR_PMDR ; 
 int /*<<< orphan*/  FXP_CSR_PORT ; 
 int FXP_FLAG_WOL ; 
 int FXP_FLAG_WOLCAP ; 
 int /*<<< orphan*/  FXP_LOCK (struct fxp_softc*) ; 
 int /*<<< orphan*/  FXP_PORT_SELECTIVE_RESET ; 
 int /*<<< orphan*/  FXP_UNLOCK (struct fxp_softc*) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 struct fxp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fxp_init_body (struct fxp_softc*,int) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fxp_resume(device_t dev)
{
	struct fxp_softc *sc = device_get_softc(dev);
	if_t ifp = sc->ifp;
	int pmc;
	uint16_t pmstat;

	FXP_LOCK(sc);

	if (pci_find_cap(sc->dev, PCIY_PMG, &pmc) == 0) {
		sc->flags &= ~FXP_FLAG_WOL;
		pmstat = pci_read_config(sc->dev, pmc + PCIR_POWER_STATUS, 2);
		/* Disable PME and clear PME status. */
		pmstat &= ~PCIM_PSTAT_PMEENABLE;
		pci_write_config(sc->dev, pmc + PCIR_POWER_STATUS, pmstat, 2);
		if ((sc->flags & FXP_FLAG_WOLCAP) != 0)
			CSR_WRITE_1(sc, FXP_CSR_PMDR,
			    CSR_READ_1(sc, FXP_CSR_PMDR));
	}

	CSR_WRITE_4(sc, FXP_CSR_PORT, FXP_PORT_SELECTIVE_RESET);
	DELAY(10);

	/* reinitialize interface if necessary */
	if (if_getflags(ifp) & IFF_UP)
		fxp_init_body(sc, 1);

	sc->suspended = 0;

	FXP_UNLOCK(sc);
	return (0);
}