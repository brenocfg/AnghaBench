#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;
struct TYPE_9__ {int flags; struct ifnet* ifp; } ;
typedef  TYPE_1__ ae_softc_t ;

/* Variables and functions */
 int AE_FLAG_TXAVAIL ; 
 int AE_ISR_DISABLE ; 
 int AE_ISR_DMAR_TIMEOUT ; 
 int AE_ISR_DMAW_TIMEOUT ; 
 int AE_ISR_PHY_LINKDOWN ; 
 int /*<<< orphan*/  AE_ISR_REG ; 
 int AE_ISR_RX_EVENT ; 
 int AE_ISR_TX_EVENT ; 
 int /*<<< orphan*/  AE_LOCK (TYPE_1__*) ; 
 int AE_READ_4 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  AE_WRITE_4 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ae_init_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  ae_rx_intr (TYPE_1__*) ; 
 int /*<<< orphan*/  ae_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  ae_tx_intr (TYPE_1__*) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,int) ; 

__attribute__((used)) static void
ae_int_task(void *arg, int pending)
{
	ae_softc_t *sc;
	struct ifnet *ifp;
	uint32_t val;

	sc = (ae_softc_t *)arg;

	AE_LOCK(sc);

	ifp = sc->ifp;

	val = AE_READ_4(sc, AE_ISR_REG);	/* Read interrupt status. */
	if (val == 0) {
		AE_UNLOCK(sc);
		return;
	}

	/*
	 * Clear interrupts and disable them.
	 */
	AE_WRITE_4(sc, AE_ISR_REG, val | AE_ISR_DISABLE);

#ifdef AE_DEBUG
	if_printf(ifp, "Interrupt received: 0x%08x\n", val);
#endif

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
		if ((val & (AE_ISR_DMAR_TIMEOUT | AE_ISR_DMAW_TIMEOUT |
		    AE_ISR_PHY_LINKDOWN)) != 0) {
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			ae_init_locked(sc);
			AE_UNLOCK(sc);
			return;
		}
		if ((val & AE_ISR_TX_EVENT) != 0)
			ae_tx_intr(sc);
		if ((val & AE_ISR_RX_EVENT) != 0)
			ae_rx_intr(sc);
		/*
		 * Re-enable interrupts.
		 */
		AE_WRITE_4(sc, AE_ISR_REG, 0);

		if ((sc->flags & AE_FLAG_TXAVAIL) != 0) {
			if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
				ae_start_locked(ifp);
		}
	}

	AE_UNLOCK(sc);
}