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
struct fxp_softc {scalar_t__ suspended; int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int CSR_READ_1 (struct fxp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct fxp_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FXP_CSR_SCB_STATACK ; 
 int /*<<< orphan*/  FXP_LOCK (struct fxp_softc*) ; 
 int /*<<< orphan*/  FXP_UNLOCK (struct fxp_softc*) ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  fxp_intr_body (struct fxp_softc*,int /*<<< orphan*/ ,int,int) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fxp_intr(void *xsc)
{
	struct fxp_softc *sc = xsc;
	if_t ifp = sc->ifp;
	uint8_t statack;

	FXP_LOCK(sc);
	if (sc->suspended) {
		FXP_UNLOCK(sc);
		return;
	}

#ifdef DEVICE_POLLING
	if (if_getcapenable(ifp) & IFCAP_POLLING) {
		FXP_UNLOCK(sc);
		return;
	}
#endif
	while ((statack = CSR_READ_1(sc, FXP_CSR_SCB_STATACK)) != 0) {
		/*
		 * It should not be possible to have all bits set; the
		 * FXP_SCB_INTR_SWI bit always returns 0 on a read.  If
		 * all bits are set, this may indicate that the card has
		 * been physically ejected, so ignore it.
		 */
		if (statack == 0xff) {
			FXP_UNLOCK(sc);
			return;
		}

		/*
		 * First ACK all the interrupts in this pass.
		 */
		CSR_WRITE_1(sc, FXP_CSR_SCB_STATACK, statack);
		if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0)
			fxp_intr_body(sc, ifp, statack, -1);
	}
	FXP_UNLOCK(sc);
}