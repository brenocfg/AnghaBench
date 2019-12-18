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
typedef  int /*<<< orphan*/  tmd ;
struct mbuf {int dummy; } ;
struct letmd {int tmd1_bits; int tmd2; scalar_t__ tmd3; } ;
struct lance_softc {int sc_last_td; int sc_no_td; int sc_ntbuf; int sc_flags; int sc_wdog_timer; int /*<<< orphan*/  (* sc_wrcsr ) (struct lance_softc*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* sc_copytodesc ) (struct lance_softc*,struct letmd*,int,int) ;int /*<<< orphan*/  (* sc_copyfromdesc ) (struct lance_softc*,struct letmd*,int,int) ;struct ifnet* sc_ifp; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int ETHERMTU ; 
 int ETHER_HDR_LEN ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int LE_C0_INEA ; 
 int LE_C0_TDMD ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int LE_DEBUG ; 
 int /*<<< orphan*/  LE_LOCK_ASSERT (struct lance_softc*,int /*<<< orphan*/ ) ; 
 int LE_T1_ENP ; 
 int LE_T1_OWN ; 
 int LE_T1_STP ; 
 int /*<<< orphan*/  LE_TBUFADDR (struct lance_softc*,int) ; 
 int LE_TMDADDR (struct lance_softc*,int) ; 
 int LE_XMD2_ONES ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  am7990_xmit_print (struct lance_softc*,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,int,...) ; 
 int lance_put (struct lance_softc*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  stub1 (struct lance_softc*,struct letmd*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct lance_softc*,struct letmd*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct lance_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
am7990_start_locked(struct lance_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;
	struct letmd tmd;
	struct mbuf *m;
	int bix, enq, len, rp;

	LE_LOCK_ASSERT(sc, MA_OWNED);

	if ((ifp->if_drv_flags & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING)
		return;

	bix = sc->sc_last_td;
	enq = 0;

	for (; sc->sc_no_td < sc->sc_ntbuf &&
	    !IFQ_DRV_IS_EMPTY(&ifp->if_snd);) {
		rp = LE_TMDADDR(sc, bix);
		(*sc->sc_copyfromdesc)(sc, &tmd, rp, sizeof(tmd));

		if (tmd.tmd1_bits & LE_T1_OWN) {
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			if_printf(ifp,
			    "missing buffer, no_td = %d, last_td = %d\n",
			    sc->sc_no_td, sc->sc_last_td);
		}

		IFQ_DRV_DEQUEUE(&ifp->if_snd, m);
		if (m == NULL)
			break;

		/*
		 * If BPF is listening on this interface, let it see the packet
		 * before we commit it to the wire.
		 */
		BPF_MTAP(ifp, m);

		/*
		 * Copy the mbuf chain into the transmit buffer.
		 */
		len = lance_put(sc, LE_TBUFADDR(sc, bix), m);

#ifdef LEDEBUG
		if (len > ETHERMTU + ETHER_HDR_LEN)
			if_printf(ifp, "packet length %d\n", len);
#endif

		/*
		 * Init transmit registers, and set transmit start flag.
		 */
		tmd.tmd1_bits = LE_T1_OWN | LE_T1_STP | LE_T1_ENP;
		tmd.tmd2 = -len | LE_XMD2_ONES;
		tmd.tmd3 = 0;

		(*sc->sc_copytodesc)(sc, &tmd, rp, sizeof(tmd));

#ifdef LEDEBUG
		if (sc->sc_flags & LE_DEBUG)
			am7990_xmit_print(sc, bix);
#endif

		(*sc->sc_wrcsr)(sc, LE_CSR0, LE_C0_INEA | LE_C0_TDMD);
		enq++;

		if (++bix == sc->sc_ntbuf)
			bix = 0;

		if (++sc->sc_no_td == sc->sc_ntbuf) {
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}
	}

	sc->sc_last_td = bix;

	if (enq > 0)
		sc->sc_wdog_timer = 5;
}