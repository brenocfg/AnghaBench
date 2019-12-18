#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_2__ {struct my_chain* my_tx_head; struct my_chain* my_tx_tail; } ;
struct my_softc {TYPE_1__ my_cdata; scalar_t__ my_timer; struct ifnet* my_ifp; } ;
struct my_chain {struct my_chain* my_nextdesc; int /*<<< orphan*/ * my_mbuf; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int CSR_READ_4 (struct my_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int MY_EC ; 
 int MY_Enhanced ; 
 int MY_LC ; 
 int /*<<< orphan*/  MY_LOCK_ASSERT (struct my_softc*) ; 
 int MY_NCRMASK ; 
 int MY_NCRMask ; 
 int MY_NCRShift ; 
 int MY_OWNByNIC ; 
 int /*<<< orphan*/  MY_TCRRCR ; 
 int /*<<< orphan*/  MY_TSR ; 
 int MY_TXERR ; 
 int MY_TXSTATUS (struct my_chain*) ; 
 int MY_UNSENT ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
my_txeof(struct my_softc * sc)
{
	struct my_chain *cur_tx;
	struct ifnet   *ifp;

	MY_LOCK_ASSERT(sc);
	ifp = sc->my_ifp;
	/* Clear the timeout timer. */
	sc->my_timer = 0;
	if (sc->my_cdata.my_tx_head == NULL) {
		return;
	}
	/*
	 * Go through our tx list and free mbufs for those frames that have
	 * been transmitted.
	 */
	while (sc->my_cdata.my_tx_head->my_mbuf != NULL) {
		u_int32_t       txstat;

		cur_tx = sc->my_cdata.my_tx_head;
		txstat = MY_TXSTATUS(cur_tx);
		if ((txstat & MY_OWNByNIC) || txstat == MY_UNSENT)
			break;
		if (!(CSR_READ_4(sc, MY_TCRRCR) & MY_Enhanced)) {
			if (txstat & MY_TXERR) {
				if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
				if (txstat & MY_EC) /* excessive collision */
					if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 1);
				if (txstat & MY_LC)	/* late collision */
					if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 1);
			}
			if_inc_counter(ifp, IFCOUNTER_COLLISIONS,
			    (txstat & MY_NCRMASK) >> MY_NCRShift);
		}
		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
		m_freem(cur_tx->my_mbuf);
		cur_tx->my_mbuf = NULL;
		if (sc->my_cdata.my_tx_head == sc->my_cdata.my_tx_tail) {
			sc->my_cdata.my_tx_head = NULL;
			sc->my_cdata.my_tx_tail = NULL;
			break;
		}
		sc->my_cdata.my_tx_head = cur_tx->my_nextdesc;
	}
	if (CSR_READ_4(sc, MY_TCRRCR) & MY_Enhanced) {
		if_inc_counter(ifp, IFCOUNTER_COLLISIONS, (CSR_READ_4(sc, MY_TSR) & MY_NCRMask));
	}
	return;
}