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
typedef  int u_int ;
struct smc_softc {int smc_mask; int /*<<< orphan*/  smc_tx; int /*<<< orphan*/  smc_tq; struct mbuf* smc_pending; } ;
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int if_capenable; int /*<<< orphan*/  if_snd; struct smc_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK ; 
 int ALLOC_INT ; 
 int ETHER_CRC_LEN ; 
 int ETHER_MAX_LEN ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ IFQ_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IST ; 
 int /*<<< orphan*/  MMUCR ; 
 int MMUCR_CMD_TX_ALLOC ; 
 int /*<<< orphan*/  MSK ; 
 int PKT_CTRL_DATA_LEN ; 
 int /*<<< orphan*/  SMC_ASSERT_LOCKED (struct smc_softc*) ; 
 int TX_ALLOC_WAIT_TIME ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int m_length (struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_mmu_wait (struct smc_softc*) ; 
 int smc_read_1 (struct smc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_select_bank (struct smc_softc*,int) ; 
 int /*<<< orphan*/  smc_write_1 (struct smc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smc_write_2 (struct smc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
smc_start_locked(struct ifnet *ifp)
{
	struct smc_softc	*sc;
	struct mbuf		*m;
	u_int			len, npages, spin_count;

	sc = ifp->if_softc;
	SMC_ASSERT_LOCKED(sc);

	if (ifp->if_drv_flags & IFF_DRV_OACTIVE)
		return;
	if (IFQ_IS_EMPTY(&ifp->if_snd))
		return;

	/*
	 * Grab the next packet.  If it's too big, drop it.
	 */
	IFQ_DRV_DEQUEUE(&ifp->if_snd, m);
	len = m_length(m, NULL);
	len += (len & 1);
	if (len > ETHER_MAX_LEN - ETHER_CRC_LEN) {
		if_printf(ifp, "large packet discarded\n");
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		m_freem(m);
		return; /* XXX readcheck? */
	}

	/*
	 * Flag that we're busy.
	 */
	ifp->if_drv_flags |= IFF_DRV_OACTIVE;
	sc->smc_pending = m;

	/*
	 * Work out how many 256 byte "pages" we need.  We have to include the
	 * control data for the packet in this calculation.
	 */
	npages = (len + PKT_CTRL_DATA_LEN) >> 8;
	if (npages == 0)
		npages = 1;

	/*
	 * Request memory.
	 */
	smc_select_bank(sc, 2);
	smc_mmu_wait(sc);
	smc_write_2(sc, MMUCR, MMUCR_CMD_TX_ALLOC | npages);

	/*
	 * Spin briefly to see if the allocation succeeds.
	 */
	spin_count = TX_ALLOC_WAIT_TIME;
	do {
		if (smc_read_1(sc, IST) & ALLOC_INT) {
			smc_write_1(sc, ACK, ALLOC_INT);
			break;
		}
	} while (--spin_count);

	/*
	 * If the allocation is taking too long, unmask the alloc interrupt
	 * and wait.
	 */
	if (spin_count == 0) {
		sc->smc_mask |= ALLOC_INT;
		if ((ifp->if_capenable & IFCAP_POLLING) == 0)
			smc_write_1(sc, MSK, sc->smc_mask);
		return;
	}

	taskqueue_enqueue(sc->smc_tq, &sc->smc_tx);
}