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
struct vge_softc {int vge_flags; struct ifnet* vge_ifp; } ;
struct ifnet {int if_flags; int if_capenable; int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int CSR_READ_4 (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VGE_CR3_INT_GMSK ; 
 int /*<<< orphan*/  VGE_CRC3 ; 
 int /*<<< orphan*/  VGE_CRS3 ; 
 int VGE_FLAG_SUSPENDED ; 
 int VGE_INTRS ; 
 int /*<<< orphan*/  VGE_ISR ; 
 int VGE_ISR_HOLDOFF_RELOAD ; 
 int VGE_ISR_LINKSTS ; 
 int VGE_ISR_RXDMA_STALL ; 
 int VGE_ISR_RXNODESC ; 
 int VGE_ISR_RXOFLOW ; 
 int VGE_ISR_RXOK ; 
 int VGE_ISR_RXOK_HIPRIO ; 
 int VGE_ISR_TXDMA_STALL ; 
 int VGE_ISR_TXOK0 ; 
 int VGE_ISR_TXOK_HIPRIO ; 
 int /*<<< orphan*/  VGE_LOCK (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_RXQCSRS ; 
 int /*<<< orphan*/  VGE_RXQCSR_RUN ; 
 int /*<<< orphan*/  VGE_RXQCSR_WAK ; 
 int /*<<< orphan*/  VGE_RX_DESC_CNT ; 
 int /*<<< orphan*/  VGE_UNLOCK (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_init_locked (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_link_statchg (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_rxeof (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vge_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  vge_txeof (struct vge_softc*) ; 

__attribute__((used)) static void
vge_intr(void *arg)
{
	struct vge_softc *sc;
	struct ifnet *ifp;
	uint32_t status;

	sc = arg;
	VGE_LOCK(sc);

	ifp = sc->vge_ifp;
	if ((sc->vge_flags & VGE_FLAG_SUSPENDED) != 0 ||
	    (ifp->if_flags & IFF_UP) == 0) {
		VGE_UNLOCK(sc);
		return;
	}

#ifdef DEVICE_POLLING
	if  (ifp->if_capenable & IFCAP_POLLING) {
		status = CSR_READ_4(sc, VGE_ISR);
		CSR_WRITE_4(sc, VGE_ISR, status);
		if (status != 0xFFFFFFFF && (status & VGE_ISR_LINKSTS) != 0)
			vge_link_statchg(sc);
		VGE_UNLOCK(sc);
		return;
	}
#endif

	/* Disable interrupts */
	CSR_WRITE_1(sc, VGE_CRC3, VGE_CR3_INT_GMSK);
	status = CSR_READ_4(sc, VGE_ISR);
	CSR_WRITE_4(sc, VGE_ISR, status | VGE_ISR_HOLDOFF_RELOAD);
	/* If the card has gone away the read returns 0xffff. */
	if (status == 0xFFFFFFFF || (status & VGE_INTRS) == 0)
		goto done;
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
		if (status & (VGE_ISR_RXOK|VGE_ISR_RXOK_HIPRIO))
			vge_rxeof(sc, VGE_RX_DESC_CNT);
		if (status & (VGE_ISR_RXOFLOW|VGE_ISR_RXNODESC)) {
			vge_rxeof(sc, VGE_RX_DESC_CNT);
			CSR_WRITE_1(sc, VGE_RXQCSRS, VGE_RXQCSR_RUN);
			CSR_WRITE_1(sc, VGE_RXQCSRS, VGE_RXQCSR_WAK);
		}

		if (status & (VGE_ISR_TXOK0|VGE_ISR_TXOK_HIPRIO))
			vge_txeof(sc);

		if (status & (VGE_ISR_TXDMA_STALL|VGE_ISR_RXDMA_STALL)) {
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			vge_init_locked(sc);
		}

		if (status & VGE_ISR_LINKSTS)
			vge_link_statchg(sc);
	}
done:
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
		/* Re-enable interrupts */
		CSR_WRITE_1(sc, VGE_CRS3, VGE_CR3_INT_GMSK);

		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			vge_start_locked(ifp);
	}
	VGE_UNLOCK(sc);
}