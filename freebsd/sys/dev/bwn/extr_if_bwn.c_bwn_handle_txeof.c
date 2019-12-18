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
struct bwn_txstatus {int rtscnt; scalar_t__ ampdu; scalar_t__ im; } ;
struct bwn_stats {int /*<<< orphan*/  rts; int /*<<< orphan*/  rtsfail; } ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_mac {int mac_flags; struct bwn_softc* mac_sc; struct bwn_stats mac_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_ASSERT_LOCKED (struct bwn_softc*) ; 
 int BWN_MAC_FLAG_DMA ; 
 int /*<<< orphan*/  bwn_dma_handle_txeof (struct bwn_mac*,struct bwn_txstatus const*) ; 
 int /*<<< orphan*/  bwn_phy_txpower_check (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_pio_handle_txeof (struct bwn_mac*,struct bwn_txstatus const*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
bwn_handle_txeof(struct bwn_mac *mac, const struct bwn_txstatus *status)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct bwn_stats *stats = &mac->mac_stats;

	BWN_ASSERT_LOCKED(mac->mac_sc);

	if (status->im)
		device_printf(sc->sc_dev, "TODO: STATUS IM\n");
	if (status->ampdu)
		device_printf(sc->sc_dev, "TODO: STATUS AMPDU\n");
	if (status->rtscnt) {
		if (status->rtscnt == 0xf)
			stats->rtsfail++;
		else
			stats->rts++;
	}

	if (mac->mac_flags & BWN_MAC_FLAG_DMA) {
		bwn_dma_handle_txeof(mac, status);
	} else {
		bwn_pio_handle_txeof(mac, status);
	}

	bwn_phy_txpower_check(mac, 0);
}