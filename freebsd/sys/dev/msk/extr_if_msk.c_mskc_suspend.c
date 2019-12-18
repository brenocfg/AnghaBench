#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msk_softc {int msk_num_port; int /*<<< orphan*/  msk_pflags; TYPE_2__** msk_if; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {TYPE_1__* msk_ifp; } ;
struct TYPE_3__ {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_CTST ; 
 int /*<<< orphan*/  B0_HWE_IMSK ; 
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  CSR_READ_4 (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_RST_SET ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MSK_FLAG_SUSPEND ; 
 int /*<<< orphan*/  MSK_LOCK (struct msk_softc*) ; 
 int /*<<< orphan*/  MSK_PHY_POWERDOWN ; 
 int /*<<< orphan*/  MSK_UNLOCK (struct msk_softc*) ; 
 struct msk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msk_phy_power (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msk_stop (TYPE_2__*) ; 

__attribute__((used)) static int
mskc_suspend(device_t dev)
{
	struct msk_softc *sc;
	int i;

	sc = device_get_softc(dev);

	MSK_LOCK(sc);

	for (i = 0; i < sc->msk_num_port; i++) {
		if (sc->msk_if[i] != NULL && sc->msk_if[i]->msk_ifp != NULL &&
		    ((sc->msk_if[i]->msk_ifp->if_drv_flags &
		    IFF_DRV_RUNNING) != 0))
			msk_stop(sc->msk_if[i]);
	}

	/* Disable all interrupts. */
	CSR_WRITE_4(sc, B0_IMSK, 0);
	CSR_READ_4(sc, B0_IMSK);
	CSR_WRITE_4(sc, B0_HWE_IMSK, 0);
	CSR_READ_4(sc, B0_HWE_IMSK);

	msk_phy_power(sc, MSK_PHY_POWERDOWN);

	/* Put hardware reset. */
	CSR_WRITE_2(sc, B0_CTST, CS_RST_SET);
	sc->msk_pflags |= MSK_FLAG_SUSPEND;

	MSK_UNLOCK(sc);

	return (0);
}