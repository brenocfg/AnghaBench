#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  rx_grxpp_lo; int /*<<< orphan*/  rx_grxpp_hi; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_gtxpp_lo; int /*<<< orphan*/  tx_gtxpp_hi; } ;
struct mstat_stats {TYPE_2__ stats_rx; TYPE_1__ stats_tx; } ;
struct host_port_stats {int /*<<< orphan*/  pfc_frames_tx_lo; int /*<<< orphan*/  pfc_frames_tx_hi; int /*<<< orphan*/  pfc_frames_rx_lo; int /*<<< orphan*/  pfc_frames_rx_hi; TYPE_3__* mac_stx; } ;
struct bxe_eth_stats {int /*<<< orphan*/  pfc_frames_sent_lo; int /*<<< orphan*/  pfc_frames_sent_hi; int /*<<< orphan*/  pfc_frames_received_lo; int /*<<< orphan*/  pfc_frames_received_hi; int /*<<< orphan*/  pause_frames_sent_lo; int /*<<< orphan*/  pause_frames_sent_hi; int /*<<< orphan*/  pause_frames_received_lo; int /*<<< orphan*/  pause_frames_received_hi; int /*<<< orphan*/  etherstatspktsover1522octets_lo; int /*<<< orphan*/  etherstatspktsover1522octets_hi; int /*<<< orphan*/  etherstatspkts1024octetsto1522octets_lo; int /*<<< orphan*/  etherstatspkts1024octetsto1522octets_hi; } ;
struct bxe_softc {struct bxe_eth_stats eth_stats; } ;
struct TYPE_12__ {int /*<<< orphan*/  mstat_stats; } ;
struct TYPE_11__ {int /*<<< orphan*/  rx_grxpf; int /*<<< orphan*/  rx_grxcf; int /*<<< orphan*/  rx_grfrg; int /*<<< orphan*/  rx_grovr; int /*<<< orphan*/  rx_grund; int /*<<< orphan*/  rx_grfcs; int /*<<< orphan*/  rx_grerb; } ;
struct TYPE_10__ {int /*<<< orphan*/  tx_gtufl; int /*<<< orphan*/  tx_gterr; int /*<<< orphan*/  tx_gt16383; int /*<<< orphan*/  tx_gt9216; int /*<<< orphan*/  tx_gt4095; int /*<<< orphan*/  tx_gt2047; int /*<<< orphan*/  tx_gt1518; int /*<<< orphan*/  tx_gt1023; int /*<<< orphan*/  tx_gt511; int /*<<< orphan*/  tx_gt255; int /*<<< orphan*/  tx_gt127; int /*<<< orphan*/  tx_gt64; int /*<<< orphan*/  tx_gtxpf; } ;
struct TYPE_9__ {int /*<<< orphan*/  tx_stat_outxoffsent_lo; int /*<<< orphan*/  tx_stat_outxoffsent_hi; int /*<<< orphan*/  rx_stat_mac_xpf_lo; int /*<<< orphan*/  rx_stat_mac_xpf_hi; int /*<<< orphan*/  tx_stat_mac_16383_lo; int /*<<< orphan*/  tx_stat_mac_16383_hi; int /*<<< orphan*/  tx_stat_mac_9216_lo; int /*<<< orphan*/  tx_stat_mac_9216_hi; int /*<<< orphan*/  tx_stat_mac_4095_lo; int /*<<< orphan*/  tx_stat_mac_4095_hi; int /*<<< orphan*/  tx_stat_mac_2047_lo; int /*<<< orphan*/  tx_stat_mac_2047_hi; int /*<<< orphan*/  tx_stat_etherstatspkts1024octetsto1522octets_lo; int /*<<< orphan*/  tx_stat_etherstatspkts1024octetsto1522octets_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_STAT64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 TYPE_6__ mac_stats ; 
 int /*<<< orphan*/  port_stats ; 
 int /*<<< orphan*/  rx_stat_dot3statsfcserrors ; 
 int /*<<< orphan*/  rx_stat_dot3statsframestoolong ; 
 int /*<<< orphan*/  rx_stat_etherstatsfragments ; 
 int /*<<< orphan*/  rx_stat_etherstatsundersizepkts ; 
 int /*<<< orphan*/  rx_stat_ifhcinbadoctets ; 
 int /*<<< orphan*/  rx_stat_mac_xpf ; 
 int /*<<< orphan*/  rx_stat_maccontrolframesreceived ; 
 int /*<<< orphan*/  rx_stat_xoffstateentered ; 
 TYPE_5__ stats_rx ; 
 TYPE_4__ stats_tx ; 
 int /*<<< orphan*/  tx_stat_dot3statsinternalmactransmiterrors ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts1024octetsto1522octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts128octetsto255octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts256octetsto511octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts512octetsto1023octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts64octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts65octetsto127octets ; 
 int /*<<< orphan*/  tx_stat_flowcontroldone ; 
 int /*<<< orphan*/  tx_stat_mac_16383 ; 
 int /*<<< orphan*/  tx_stat_mac_2047 ; 
 int /*<<< orphan*/  tx_stat_mac_4095 ; 
 int /*<<< orphan*/  tx_stat_mac_9216 ; 
 int /*<<< orphan*/  tx_stat_mac_ufl ; 
 int /*<<< orphan*/  tx_stat_outxoffsent ; 

__attribute__((used)) static void
bxe_mstat_stats_update(struct bxe_softc *sc)
{
    struct host_port_stats *pstats = BXE_SP(sc, port_stats);
    struct bxe_eth_stats *estats = &sc->eth_stats;
    struct mstat_stats *new = BXE_SP(sc, mac_stats.mstat_stats);

    ADD_STAT64(stats_rx.rx_grerb, rx_stat_ifhcinbadoctets);
    ADD_STAT64(stats_rx.rx_grfcs, rx_stat_dot3statsfcserrors);
    ADD_STAT64(stats_rx.rx_grund, rx_stat_etherstatsundersizepkts);
    ADD_STAT64(stats_rx.rx_grovr, rx_stat_dot3statsframestoolong);
    ADD_STAT64(stats_rx.rx_grfrg, rx_stat_etherstatsfragments);
    ADD_STAT64(stats_rx.rx_grxcf, rx_stat_maccontrolframesreceived);
    ADD_STAT64(stats_rx.rx_grxpf, rx_stat_xoffstateentered);
    ADD_STAT64(stats_rx.rx_grxpf, rx_stat_mac_xpf);
    ADD_STAT64(stats_tx.tx_gtxpf, tx_stat_outxoffsent);
    ADD_STAT64(stats_tx.tx_gtxpf, tx_stat_flowcontroldone);

    /* collect pfc stats */
    ADD_64(pstats->pfc_frames_tx_hi, new->stats_tx.tx_gtxpp_hi,
           pstats->pfc_frames_tx_lo, new->stats_tx.tx_gtxpp_lo);
    ADD_64(pstats->pfc_frames_rx_hi, new->stats_rx.rx_grxpp_hi,
           pstats->pfc_frames_rx_lo, new->stats_rx.rx_grxpp_lo);

    ADD_STAT64(stats_tx.tx_gt64, tx_stat_etherstatspkts64octets);
    ADD_STAT64(stats_tx.tx_gt127, tx_stat_etherstatspkts65octetsto127octets);
    ADD_STAT64(stats_tx.tx_gt255, tx_stat_etherstatspkts128octetsto255octets);
    ADD_STAT64(stats_tx.tx_gt511, tx_stat_etherstatspkts256octetsto511octets);
    ADD_STAT64(stats_tx.tx_gt1023,
               tx_stat_etherstatspkts512octetsto1023octets);
    ADD_STAT64(stats_tx.tx_gt1518,
               tx_stat_etherstatspkts1024octetsto1522octets);
    ADD_STAT64(stats_tx.tx_gt2047, tx_stat_mac_2047);

    ADD_STAT64(stats_tx.tx_gt4095, tx_stat_mac_4095);
    ADD_STAT64(stats_tx.tx_gt9216, tx_stat_mac_9216);
    ADD_STAT64(stats_tx.tx_gt16383, tx_stat_mac_16383);

    ADD_STAT64(stats_tx.tx_gterr, tx_stat_dot3statsinternalmactransmiterrors);
    ADD_STAT64(stats_tx.tx_gtufl, tx_stat_mac_ufl);

    estats->etherstatspkts1024octetsto1522octets_hi =
        pstats->mac_stx[1].tx_stat_etherstatspkts1024octetsto1522octets_hi;
    estats->etherstatspkts1024octetsto1522octets_lo =
        pstats->mac_stx[1].tx_stat_etherstatspkts1024octetsto1522octets_lo;

    estats->etherstatspktsover1522octets_hi =
        pstats->mac_stx[1].tx_stat_mac_2047_hi;
    estats->etherstatspktsover1522octets_lo =
        pstats->mac_stx[1].tx_stat_mac_2047_lo;

    ADD_64(estats->etherstatspktsover1522octets_hi,
           pstats->mac_stx[1].tx_stat_mac_4095_hi,
           estats->etherstatspktsover1522octets_lo,
           pstats->mac_stx[1].tx_stat_mac_4095_lo);

    ADD_64(estats->etherstatspktsover1522octets_hi,
           pstats->mac_stx[1].tx_stat_mac_9216_hi,
           estats->etherstatspktsover1522octets_lo,
           pstats->mac_stx[1].tx_stat_mac_9216_lo);

    ADD_64(estats->etherstatspktsover1522octets_hi,
           pstats->mac_stx[1].tx_stat_mac_16383_hi,
           estats->etherstatspktsover1522octets_lo,
           pstats->mac_stx[1].tx_stat_mac_16383_lo);

    estats->pause_frames_received_hi = pstats->mac_stx[1].rx_stat_mac_xpf_hi;
    estats->pause_frames_received_lo = pstats->mac_stx[1].rx_stat_mac_xpf_lo;

    estats->pause_frames_sent_hi = pstats->mac_stx[1].tx_stat_outxoffsent_hi;
    estats->pause_frames_sent_lo = pstats->mac_stx[1].tx_stat_outxoffsent_lo;

    estats->pfc_frames_received_hi = pstats->pfc_frames_rx_hi;
    estats->pfc_frames_received_lo = pstats->pfc_frames_rx_lo;
    estats->pfc_frames_sent_hi = pstats->pfc_frames_tx_hi;
    estats->pfc_frames_sent_lo = pstats->pfc_frames_tx_lo;
}