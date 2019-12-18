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
struct hn_tx_ring {int hn_agg_szmax; int hn_agg_pktmax; int hn_agg_align; int /*<<< orphan*/  hn_tx_lock; } ;
struct hn_softc {scalar_t__ hn_agg_size; int hn_rndis_agg_size; int hn_chim_szmax; int hn_rndis_agg_align; scalar_t__ hn_agg_pkts; int hn_rndis_agg_pkts; int hn_tx_ring_cnt; struct hn_tx_ring* hn_tx_ring; int /*<<< orphan*/  hn_ifp; } ;

/* Variables and functions */
 int HN_PKTSIZE_MIN (int) ; 
 int INT_MAX ; 
 int SHRT_MAX ; 
 int UINT32_MAX ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_set_txagg(struct hn_softc *sc)
{
	uint32_t size, pkts;
	int i;

	/*
	 * Setup aggregation size.
	 */
	if (sc->hn_agg_size < 0)
		size = UINT32_MAX;
	else
		size = sc->hn_agg_size;

	if (sc->hn_rndis_agg_size < size)
		size = sc->hn_rndis_agg_size;

	/* NOTE: We only aggregate packets using chimney sending buffers. */
	if (size > (uint32_t)sc->hn_chim_szmax)
		size = sc->hn_chim_szmax;

	if (size <= 2 * HN_PKTSIZE_MIN(sc->hn_rndis_agg_align)) {
		/* Disable */
		size = 0;
		pkts = 0;
		goto done;
	}

	/* NOTE: Type of the per TX ring setting is 'int'. */
	if (size > INT_MAX)
		size = INT_MAX;

	/*
	 * Setup aggregation packet count.
	 */
	if (sc->hn_agg_pkts < 0)
		pkts = UINT32_MAX;
	else
		pkts = sc->hn_agg_pkts;

	if (sc->hn_rndis_agg_pkts < pkts)
		pkts = sc->hn_rndis_agg_pkts;

	if (pkts <= 1) {
		/* Disable */
		size = 0;
		pkts = 0;
		goto done;
	}

	/* NOTE: Type of the per TX ring setting is 'short'. */
	if (pkts > SHRT_MAX)
		pkts = SHRT_MAX;

done:
	/* NOTE: Type of the per TX ring setting is 'short'. */
	if (sc->hn_rndis_agg_align > SHRT_MAX) {
		/* Disable */
		size = 0;
		pkts = 0;
	}

	if (bootverbose) {
		if_printf(sc->hn_ifp, "TX agg size %u, pkts %u, align %u\n",
		    size, pkts, sc->hn_rndis_agg_align);
	}

	for (i = 0; i < sc->hn_tx_ring_cnt; ++i) {
		struct hn_tx_ring *txr = &sc->hn_tx_ring[i];

		mtx_lock(&txr->hn_tx_lock);
		txr->hn_agg_szmax = size;
		txr->hn_agg_pktmax = pkts;
		txr->hn_agg_align = sc->hn_rndis_agg_align;
		mtx_unlock(&txr->hn_tx_lock);
	}
}