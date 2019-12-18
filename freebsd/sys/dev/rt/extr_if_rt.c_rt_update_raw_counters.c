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
struct rt_softc {int /*<<< orphan*/  rx_fifo_overflows; int /*<<< orphan*/  rx_phy_err; int /*<<< orphan*/  rx_long_err; int /*<<< orphan*/  rx_short_err; int /*<<< orphan*/  rx_crc_err; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_collision; int /*<<< orphan*/  tx_skip; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;

/* Variables and functions */
 scalar_t__ CNTR_BASE ; 
 scalar_t__ GDMA_RX_CSUM_ERCNT0 ; 
 scalar_t__ GDMA_RX_FERCNT0 ; 
 scalar_t__ GDMA_RX_GBCNT0 ; 
 scalar_t__ GDMA_RX_GPCNT0 ; 
 scalar_t__ GDMA_RX_LONG_ERCNT0 ; 
 scalar_t__ GDMA_RX_OERCNT0 ; 
 scalar_t__ GDMA_RX_SHORT_ERCNT0 ; 
 scalar_t__ GDMA_TX_COLCNT0 ; 
 scalar_t__ GDMA_TX_GBCNT0 ; 
 scalar_t__ GDMA_TX_GPCNT0 ; 
 scalar_t__ GDMA_TX_SKIPCNT0 ; 
 scalar_t__ RT_READ (struct rt_softc*,scalar_t__) ; 

__attribute__((used)) static void
rt_update_raw_counters(struct rt_softc *sc)
{

	sc->tx_bytes	+= RT_READ(sc, CNTR_BASE + GDMA_TX_GBCNT0);
	sc->tx_packets	+= RT_READ(sc, CNTR_BASE + GDMA_TX_GPCNT0);
	sc->tx_skip	+= RT_READ(sc, CNTR_BASE + GDMA_TX_SKIPCNT0);
	sc->tx_collision+= RT_READ(sc, CNTR_BASE + GDMA_TX_COLCNT0);

	sc->rx_bytes	+= RT_READ(sc, CNTR_BASE + GDMA_RX_GBCNT0);
	sc->rx_packets	+= RT_READ(sc, CNTR_BASE + GDMA_RX_GPCNT0);
	sc->rx_crc_err	+= RT_READ(sc, CNTR_BASE + GDMA_RX_CSUM_ERCNT0);
	sc->rx_short_err+= RT_READ(sc, CNTR_BASE + GDMA_RX_SHORT_ERCNT0);
	sc->rx_long_err	+= RT_READ(sc, CNTR_BASE + GDMA_RX_LONG_ERCNT0);
	sc->rx_phy_err	+= RT_READ(sc, CNTR_BASE + GDMA_RX_FERCNT0);
	sc->rx_fifo_overflows+= RT_READ(sc, CNTR_BASE + GDMA_RX_OERCNT0);
}