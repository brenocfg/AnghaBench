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
struct ifnet {int /*<<< orphan*/  if_snd; } ;
struct fv_softc {int sc_inten; int sc_rxint_mask; int sc_txint_mask; int /*<<< orphan*/  fv_dev; struct ifnet* fv_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_FULLDUP ; 
 int CSR_READ_4 (struct fv_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_STATUS ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct fv_softc*,int /*<<< orphan*/ ,int) ; 
 int FULLDUP_CS ; 
 int FULLDUP_NRP_SHIFT ; 
 int FULLDUP_NTP_SHIFT ; 
 int FULLDUP_RT_SHIFT ; 
 int FULLDUP_TT_SHIFT ; 
 int /*<<< orphan*/  FV_LOCK (struct fv_softc*) ; 
 int /*<<< orphan*/  FV_UNLOCK (struct fv_softc*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int STATUS_AIS ; 
 int STATUS_UNF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fv_rx (struct fv_softc*) ; 
 int /*<<< orphan*/  fv_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  fv_tx (struct fv_softc*) ; 

__attribute__((used)) static void
fv_intr(void *arg)
{
	struct fv_softc		*sc = arg;
	uint32_t		status;
	struct ifnet		*ifp = sc->fv_ifp;

	FV_LOCK(sc);

	status = CSR_READ_4(sc, CSR_STATUS);
	/* mask out interrupts */
	while((status & sc->sc_inten) != 0) {
		if (status) {
			CSR_WRITE_4(sc, CSR_STATUS, status);
		}
		if (status & STATUS_UNF) {
			device_printf(sc->fv_dev, "Transmit Underflow\n");
		}
		if (status & sc->sc_rxint_mask) {
			fv_rx(sc);
		}
		if (status & sc->sc_txint_mask) {
			fv_tx(sc);
		}
		if (status & STATUS_AIS) {
			device_printf(sc->fv_dev, "Abnormal Interrupt %x\n",
			    status);
		}
		CSR_WRITE_4(sc, CSR_FULLDUP, FULLDUP_CS | 
		    (1 << FULLDUP_TT_SHIFT) | (3 << FULLDUP_NTP_SHIFT) | 
		    (2 << FULLDUP_RT_SHIFT) | (2 << FULLDUP_NRP_SHIFT));


		status = CSR_READ_4(sc, CSR_STATUS);
	}

	/* Try to get more packets going. */
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		fv_start_locked(ifp);

	FV_UNLOCK(sc);
}