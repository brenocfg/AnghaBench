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
typedef  int u_int32_t ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;
struct bfe_softc {int /*<<< orphan*/  bfe_dev; struct ifnet* bfe_ifp; } ;

/* Variables and functions */
 int BFE_IMASK_DEF ; 
 int /*<<< orphan*/  BFE_ISTAT ; 
 int BFE_ISTAT_DPE ; 
 int BFE_ISTAT_DSCE ; 
 int BFE_ISTAT_ERRORS ; 
 int BFE_ISTAT_RX ; 
 int BFE_ISTAT_TX ; 
 int /*<<< orphan*/  BFE_LOCK (struct bfe_softc*) ; 
 int /*<<< orphan*/  BFE_UNLOCK (struct bfe_softc*) ; 
 int CSR_READ_4 (struct bfe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bfe_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfe_init_locked (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_rxeof (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  bfe_stop (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_txeof (struct bfe_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
bfe_intr(void *xsc)
{
	struct bfe_softc *sc = xsc;
	struct ifnet *ifp;
	u_int32_t istat;

	ifp = sc->bfe_ifp;

	BFE_LOCK(sc);

	istat = CSR_READ_4(sc, BFE_ISTAT);

	/*
	 * Defer unsolicited interrupts - This is necessary because setting the
	 * chips interrupt mask register to 0 doesn't actually stop the
	 * interrupts
	 */
	istat &= BFE_IMASK_DEF;
	CSR_WRITE_4(sc, BFE_ISTAT, istat);
	CSR_READ_4(sc, BFE_ISTAT);

	/* not expecting this interrupt, disregard it */
	if (istat == 0 || (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		BFE_UNLOCK(sc);
		return;
	}

	/* A packet was received */
	if (istat & BFE_ISTAT_RX)
		bfe_rxeof(sc);

	/* A packet was sent */
	if (istat & BFE_ISTAT_TX)
		bfe_txeof(sc);

	if (istat & BFE_ISTAT_ERRORS) {

		if (istat & BFE_ISTAT_DSCE) {
			device_printf(sc->bfe_dev, "Descriptor Error\n");
			bfe_stop(sc);
			BFE_UNLOCK(sc);
			return;
		}

		if (istat & BFE_ISTAT_DPE) {
			device_printf(sc->bfe_dev,
			    "Descriptor Protocol Error\n");
			bfe_stop(sc);
			BFE_UNLOCK(sc);
			return;
		}
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		bfe_init_locked(sc);
	}

	/* We have packets pending, fire them out */
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		bfe_start_locked(ifp);

	BFE_UNLOCK(sc);
}