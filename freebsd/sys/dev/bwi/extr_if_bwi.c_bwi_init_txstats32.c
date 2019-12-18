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
struct bwi_txstats_data {int stats_paddr; int /*<<< orphan*/  stats_ring_paddr; int /*<<< orphan*/  stats_ctrl_base; int /*<<< orphan*/  stats_ring_dmap; int /*<<< orphan*/  stats_ring_dtag; int /*<<< orphan*/  stats_ring; scalar_t__ stats_idx; int /*<<< orphan*/  stats_dmap; int /*<<< orphan*/  stats_dtag; int /*<<< orphan*/  stats; } ;
struct bwi_txstats {int dummy; } ;
struct bwi_softc {struct bwi_txstats_data* sc_txstats; } ;
typedef  int bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int BWI_TXSTATS_NDESC ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_init_rxdesc_ring32 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwi_setup_desc32 (struct bwi_softc*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bwi_init_txstats32(struct bwi_softc *sc)
{
	struct bwi_txstats_data *st = sc->sc_txstats;
	bus_addr_t stats_paddr;
	int i;

	bzero(st->stats, BWI_TXSTATS_NDESC * sizeof(struct bwi_txstats));
	bus_dmamap_sync(st->stats_dtag, st->stats_dmap, BUS_DMASYNC_PREWRITE);

	st->stats_idx = 0;

	stats_paddr = st->stats_paddr;
	for (i = 0; i < BWI_TXSTATS_NDESC; ++i) {
		bwi_setup_desc32(sc, st->stats_ring, BWI_TXSTATS_NDESC, i,
				 stats_paddr, sizeof(struct bwi_txstats), 0);
		stats_paddr += sizeof(struct bwi_txstats);
	}
	bus_dmamap_sync(st->stats_ring_dtag, st->stats_ring_dmap,
			BUS_DMASYNC_PREWRITE);

	bwi_init_rxdesc_ring32(sc, st->stats_ctrl_base,
			       st->stats_ring_paddr, 0, BWI_TXSTATS_NDESC);
	return 0;
}