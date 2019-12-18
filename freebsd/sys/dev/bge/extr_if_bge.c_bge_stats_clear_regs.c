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
struct bge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_RXLP_LOCSTAT_DMA_HPWRQ_FULL ; 
 int /*<<< orphan*/  BGE_RXLP_LOCSTAT_DMA_WRQ_FULL ; 
 int /*<<< orphan*/  BGE_RXLP_LOCSTAT_FILTDROP ; 
 int /*<<< orphan*/  BGE_RXLP_LOCSTAT_IFIN_DROPS ; 
 int /*<<< orphan*/  BGE_RXLP_LOCSTAT_IFIN_ERRORS ; 
 int /*<<< orphan*/  BGE_RXLP_LOCSTAT_OUT_OF_BDS ; 
 int /*<<< orphan*/  BGE_RXLP_LOCSTAT_RXTHRESH_HIT ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_ALGIN_ERRORS ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_BCAST ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_CTRL_RCVD ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_FCS_ERRORS ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_FRAGMENTS ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_FRAME_TOO_LONG ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_JABBERS ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_MCAST ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_OCTESTS ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_UCAST ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_UNDERSIZE ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_XOFF_ENTERED ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_XOFF_RCVD ; 
 int /*<<< orphan*/  BGE_RX_MAC_STATS_XON_RCVD ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_BCAST ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_COLLS ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_DEFERRED ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_ERRORS ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_EXCESS_COLL ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_LATE_COLL ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_MCAST ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_MULTI_COLL ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_OCTETS ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_SINGLE_COLL ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_UCAST ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_XOFF_SENT ; 
 int /*<<< orphan*/  BGE_TX_MAC_STATS_XON_SENT ; 
 int /*<<< orphan*/  CSR_READ_4 (struct bge_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bge_stats_clear_regs(struct bge_softc *sc)
{

	CSR_READ_4(sc, BGE_TX_MAC_STATS_OCTETS);
	CSR_READ_4(sc, BGE_TX_MAC_STATS_COLLS);
	CSR_READ_4(sc, BGE_TX_MAC_STATS_XON_SENT);
	CSR_READ_4(sc, BGE_TX_MAC_STATS_XOFF_SENT);
	CSR_READ_4(sc, BGE_TX_MAC_STATS_ERRORS);
	CSR_READ_4(sc, BGE_TX_MAC_STATS_SINGLE_COLL);
	CSR_READ_4(sc, BGE_TX_MAC_STATS_MULTI_COLL);
	CSR_READ_4(sc, BGE_TX_MAC_STATS_DEFERRED);
	CSR_READ_4(sc, BGE_TX_MAC_STATS_EXCESS_COLL);
	CSR_READ_4(sc, BGE_TX_MAC_STATS_LATE_COLL);
	CSR_READ_4(sc, BGE_TX_MAC_STATS_UCAST);
	CSR_READ_4(sc, BGE_TX_MAC_STATS_MCAST);
	CSR_READ_4(sc, BGE_TX_MAC_STATS_BCAST);

	CSR_READ_4(sc, BGE_RX_MAC_STATS_OCTESTS);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_FRAGMENTS);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_UCAST);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_MCAST);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_BCAST);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_FCS_ERRORS);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_ALGIN_ERRORS);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_XON_RCVD);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_XOFF_RCVD);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_CTRL_RCVD);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_XOFF_ENTERED);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_FRAME_TOO_LONG);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_JABBERS);
	CSR_READ_4(sc, BGE_RX_MAC_STATS_UNDERSIZE);

	CSR_READ_4(sc, BGE_RXLP_LOCSTAT_FILTDROP);
	CSR_READ_4(sc, BGE_RXLP_LOCSTAT_DMA_WRQ_FULL);
	CSR_READ_4(sc, BGE_RXLP_LOCSTAT_DMA_HPWRQ_FULL);
	CSR_READ_4(sc, BGE_RXLP_LOCSTAT_OUT_OF_BDS);
	CSR_READ_4(sc, BGE_RXLP_LOCSTAT_IFIN_DROPS);
	CSR_READ_4(sc, BGE_RXLP_LOCSTAT_IFIN_ERRORS);
	CSR_READ_4(sc, BGE_RXLP_LOCSTAT_RXTHRESH_HIT);
}