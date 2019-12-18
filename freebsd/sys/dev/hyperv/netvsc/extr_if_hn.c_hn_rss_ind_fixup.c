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
struct ndis_rssprm_toeplitz {int* rss_ind; } ;
struct hn_softc {int hn_rx_ring_inuse; int /*<<< orphan*/  hn_ifp; struct ndis_rssprm_toeplitz hn_rss; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NDIS_HASH_INDCNT ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static void
hn_rss_ind_fixup(struct hn_softc *sc)
{
	struct ndis_rssprm_toeplitz *rss = &sc->hn_rss;
	int i, nchan;

	nchan = sc->hn_rx_ring_inuse;
	KASSERT(nchan > 1, ("invalid # of channels %d", nchan));

	/*
	 * Check indirect table to make sure that all channels in it
	 * can be used.
	 */
	for (i = 0; i < NDIS_HASH_INDCNT; ++i) {
		if (rss->rss_ind[i] >= nchan) {
			if_printf(sc->hn_ifp,
			    "RSS indirect table %d fixup: %u -> %d\n",
			    i, rss->rss_ind[i], nchan - 1);
			rss->rss_ind[i] = nchan - 1;
		}
	}
}