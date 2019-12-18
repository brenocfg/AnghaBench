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
struct bwi_txstats_data {int stats_idx; struct bwi_txstats* stats; int /*<<< orphan*/  stats_dmap; int /*<<< orphan*/  stats_dtag; } ;
struct bwi_txstats {int txs_flags; int /*<<< orphan*/  txs_id; int /*<<< orphan*/  txs_txcnt; } ;
struct bwi_softc {struct bwi_txstats_data* sc_txstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int BWI_TXSTATS_NDESC ; 
 int BWI_TXS_F_ACKED ; 
 int BWI_TXS_F_PENDING ; 
 int /*<<< orphan*/  BWI_TXS_TXCNT_DATA ; 
 int __SHIFTOUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bwi_txeof (struct bwi_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwi_txeof_status(struct bwi_softc *sc, int end_idx)
{
	struct bwi_txstats_data *st = sc->sc_txstats;
	int idx;

	bus_dmamap_sync(st->stats_dtag, st->stats_dmap, BUS_DMASYNC_POSTREAD);

	idx = st->stats_idx;
	while (idx != end_idx) {
		const struct bwi_txstats *stats = &st->stats[idx];

		if ((stats->txs_flags & BWI_TXS_F_PENDING) == 0) {
			int data_txcnt;

			data_txcnt = __SHIFTOUT(stats->txs_txcnt,
						BWI_TXS_TXCNT_DATA);
			_bwi_txeof(sc, le16toh(stats->txs_id),
				   stats->txs_flags & BWI_TXS_F_ACKED,
				   data_txcnt);
		}
		idx = (idx + 1) % BWI_TXSTATS_NDESC;
	}
	st->stats_idx = idx;
}