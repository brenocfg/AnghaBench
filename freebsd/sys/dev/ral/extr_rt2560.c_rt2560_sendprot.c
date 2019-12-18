#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rt2560_tx_desc {int dummy; } ;
struct rt2560_tx_data {int /*<<< orphan*/  map; int /*<<< orphan*/  rix; int /*<<< orphan*/  ni; struct mbuf* m; } ;
struct TYPE_8__ {size_t cur_encrypt; int /*<<< orphan*/  queued; int /*<<< orphan*/  data_dmat; struct rt2560_tx_data* data; struct rt2560_tx_desc* desc; } ;
struct rt2560_softc {TYPE_3__ txq; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct ieee80211com {int /*<<< orphan*/  ic_rt; } ;
struct ieee80211_node {TYPE_1__* ni_vap; struct ieee80211com* ni_ic; } ;
struct TYPE_9__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_4__ bus_dma_segment_t ;
struct TYPE_6__ {int /*<<< orphan*/  iv_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  IEEE80211_FIXED_RATE_NONE ; 
 int IEEE80211_PROT_RTSCTS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int RT2560_MAX_SCATTER ; 
 int RT2560_TX_ACK ; 
 int RT2560_TX_MORE_FRAG ; 
 int RT2560_TX_RING_COUNT ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,TYPE_4__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 struct mbuf* ieee80211_alloc_prot (struct ieee80211_node*,struct mbuf const*,int,int) ; 
 int ieee80211_ctl_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_ref_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  rt2560_setup_tx_desc (struct rt2560_softc*,struct rt2560_tx_desc*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rt2560_sendprot(struct rt2560_softc *sc,
    const struct mbuf *m, struct ieee80211_node *ni, int prot, int rate)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct rt2560_tx_desc *desc;
	struct rt2560_tx_data *data;
	struct mbuf *mprot;
	int protrate, flags, error;
	bus_dma_segment_t segs[RT2560_MAX_SCATTER];
	int nsegs;

	mprot = ieee80211_alloc_prot(ni, m, rate, prot);
	if (mprot == NULL) {
		if_inc_counter(ni->ni_vap->iv_ifp, IFCOUNTER_OERRORS, 1);
		device_printf(sc->sc_dev,
		    "could not allocate mbuf for protection mode %d\n", prot);
		return ENOBUFS;
	}

	desc = &sc->txq.desc[sc->txq.cur_encrypt];
	data = &sc->txq.data[sc->txq.cur_encrypt];

	error = bus_dmamap_load_mbuf_sg(sc->txq.data_dmat, data->map,
	    mprot, segs, &nsegs, 0);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "could not map mbuf (error %d)\n", error);
		m_freem(mprot);
		return error;
	}

	data->m = mprot;
	data->ni = ieee80211_ref_node(ni);
	/* ctl frames are not taken into account for amrr */
	data->rix = IEEE80211_FIXED_RATE_NONE;

	protrate = ieee80211_ctl_rate(ic->ic_rt, rate);
	flags = RT2560_TX_MORE_FRAG;
	if (prot == IEEE80211_PROT_RTSCTS)
		flags |= RT2560_TX_ACK;

	rt2560_setup_tx_desc(sc, desc, flags, mprot->m_pkthdr.len, protrate, 1,
	    segs->ds_addr);

	bus_dmamap_sync(sc->txq.data_dmat, data->map,
	    BUS_DMASYNC_PREWRITE);

	sc->txq.queued++;
	sc->txq.cur_encrypt = (sc->txq.cur_encrypt + 1) % RT2560_TX_RING_COUNT;

	return 0;
}