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
struct ipw_softc {int /*<<< orphan*/  sc_tx_timer; int /*<<< orphan*/  free_sbuf; int /*<<< orphan*/  txbuf_dmat; int /*<<< orphan*/  free_shdr; int /*<<< orphan*/  hdr_dmat; int /*<<< orphan*/  cmd_map; int /*<<< orphan*/  cmd_dmat; } ;
struct ipw_soft_hdr {int /*<<< orphan*/  m; int /*<<< orphan*/  ni; int /*<<< orphan*/  map; } ;
struct ipw_soft_buf {int /*<<< orphan*/  m; int /*<<< orphan*/  ni; int /*<<< orphan*/  map; } ;
struct ipw_soft_bd {int type; struct ipw_soft_hdr* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
#define  IPW_SBD_TYPE_COMMAND 130 
#define  IPW_SBD_TYPE_DATA 129 
#define  IPW_SBD_TYPE_HEADER 128 
 int IPW_SBD_TYPE_NOASSOC ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ipw_soft_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
ipw_release_sbd(struct ipw_softc *sc, struct ipw_soft_bd *sbd)
{
	struct ipw_soft_hdr *shdr;
	struct ipw_soft_buf *sbuf;

	switch (sbd->type) {
	case IPW_SBD_TYPE_COMMAND:
		bus_dmamap_sync(sc->cmd_dmat, sc->cmd_map,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->cmd_dmat, sc->cmd_map);
		break;

	case IPW_SBD_TYPE_HEADER:
		shdr = sbd->priv;
		bus_dmamap_sync(sc->hdr_dmat, shdr->map, BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->hdr_dmat, shdr->map);
		SLIST_INSERT_HEAD(&sc->free_shdr, shdr, next);
		break;

	case IPW_SBD_TYPE_DATA:
		sbuf = sbd->priv;
		bus_dmamap_sync(sc->txbuf_dmat, sbuf->map,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->txbuf_dmat, sbuf->map);
		SLIST_INSERT_HEAD(&sc->free_sbuf, sbuf, next);

		ieee80211_tx_complete(sbuf->ni, sbuf->m, 0/*XXX*/);

		sc->sc_tx_timer = 0;
		break;
	}

	sbd->type = IPW_SBD_TYPE_NOASSOC;
}