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
struct fxp_softc {int suspended; int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FXP_FLAG_WOL ; 
 int /*<<< orphan*/  FXP_LOCK (struct fxp_softc*) ; 
 int /*<<< orphan*/  FXP_UNLOCK (struct fxp_softc*) ; 
 int IFCAP_WOL_MAGIC ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int PCIM_PSTAT_PME ; 
 int PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 struct fxp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fxp_init_body (struct fxp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fxp_stop (struct fxp_softc*) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int
fxp_suspend(device_t dev)
{
	struct fxp_softc *sc = device_get_softc(dev);
	if_t ifp;
	int pmc;
	uint16_t pmstat;

	FXP_LOCK(sc);

	ifp = sc->ifp;
	if (pci_find_cap(sc->dev, PCIY_PMG, &pmc) == 0) {
		pmstat = pci_read_config(sc->dev, pmc + PCIR_POWER_STATUS, 2);
		pmstat &= ~(PCIM_PSTAT_PME | PCIM_PSTAT_PMEENABLE);
		if ((if_getcapenable(ifp) & IFCAP_WOL_MAGIC) != 0) {
			/* Request PME. */
			pmstat |= PCIM_PSTAT_PME | PCIM_PSTAT_PMEENABLE;
			sc->flags |= FXP_FLAG_WOL;
			/* Reconfigure hardware to accept magic frames. */
			if_setdrvflagbits(ifp, 0, IFF_DRV_RUNNING);
			fxp_init_body(sc, 0);
		}
		pci_write_config(sc->dev, pmc + PCIR_POWER_STATUS, pmstat, 2);
	}
	fxp_stop(sc);

	sc->suspended = 1;

	FXP_UNLOCK(sc);
	return (0);
}