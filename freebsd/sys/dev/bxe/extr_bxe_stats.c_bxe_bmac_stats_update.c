#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct host_port_stats {int /*<<< orphan*/  pfc_frames_tx_lo; int /*<<< orphan*/  pfc_frames_tx_hi; int /*<<< orphan*/  pfc_frames_rx_lo; int /*<<< orphan*/  pfc_frames_rx_hi; TYPE_1__* mac_stx; } ;
struct bxe_fw_port_stats_old {int /*<<< orphan*/  pfc_frames_rx_lo; int /*<<< orphan*/  pfc_frames_rx_hi; int /*<<< orphan*/  pfc_frames_tx_lo; int /*<<< orphan*/  pfc_frames_tx_hi; } ;
struct bxe_eth_stats {int /*<<< orphan*/  pfc_frames_sent_lo; int /*<<< orphan*/  pfc_frames_sent_hi; int /*<<< orphan*/  pfc_frames_received_lo; int /*<<< orphan*/  pfc_frames_received_hi; int /*<<< orphan*/  pause_frames_sent_lo; int /*<<< orphan*/  pause_frames_sent_hi; int /*<<< orphan*/  pause_frames_received_lo; int /*<<< orphan*/  pause_frames_received_hi; } ;
struct bxe_softc {struct bxe_fw_port_stats_old fw_stats_old; struct bxe_eth_stats eth_stats; } ;
struct bmac2_stats {int /*<<< orphan*/  rx_stat_grpp_lo; int /*<<< orphan*/  rx_stat_grpp_hi; int /*<<< orphan*/  tx_stat_gtpp_lo; int /*<<< orphan*/  tx_stat_gtpp_hi; } ;
struct bmac1_stats {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bmac2_stats; int /*<<< orphan*/  bmac1_stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_stat_outxoffsent_lo; int /*<<< orphan*/  tx_stat_outxoffsent_hi; int /*<<< orphan*/  rx_stat_mac_xpf_lo; int /*<<< orphan*/  rx_stat_mac_xpf_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ CHIP_IS_E1x (struct bxe_softc*) ; 
 int /*<<< orphan*/  UPDATE_STAT64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ mac_stats ; 
 int /*<<< orphan*/  port_stats ; 
 int /*<<< orphan*/  rx_stat_dot3statsfcserrors ; 
 int /*<<< orphan*/  rx_stat_dot3statsframestoolong ; 
 int /*<<< orphan*/  rx_stat_etherstatsfragments ; 
 int /*<<< orphan*/  rx_stat_etherstatsjabbers ; 
 int /*<<< orphan*/  rx_stat_etherstatsundersizepkts ; 
 int /*<<< orphan*/  rx_stat_grerb ; 
 int /*<<< orphan*/  rx_stat_grfcs ; 
 int /*<<< orphan*/  rx_stat_grfrg ; 
 int /*<<< orphan*/  rx_stat_grjbr ; 
 int /*<<< orphan*/  rx_stat_grovr ; 
 int /*<<< orphan*/  rx_stat_grund ; 
 int /*<<< orphan*/  rx_stat_grxcf ; 
 int /*<<< orphan*/  rx_stat_grxpf ; 
 int /*<<< orphan*/  rx_stat_ifhcinbadoctets ; 
 int /*<<< orphan*/  rx_stat_mac_xpf ; 
 int /*<<< orphan*/  rx_stat_maccontrolframesreceived ; 
 int /*<<< orphan*/  rx_stat_xoffstateentered ; 
 int /*<<< orphan*/  tx_stat_dot3statsinternalmactransmiterrors ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts1024octetsto1522octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts128octetsto255octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts256octetsto511octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts512octetsto1023octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts64octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts65octetsto127octets ; 
 int /*<<< orphan*/  tx_stat_flowcontroldone ; 
 int /*<<< orphan*/  tx_stat_gt1023 ; 
 int /*<<< orphan*/  tx_stat_gt127 ; 
 int /*<<< orphan*/  tx_stat_gt1518 ; 
 int /*<<< orphan*/  tx_stat_gt16383 ; 
 int /*<<< orphan*/  tx_stat_gt2047 ; 
 int /*<<< orphan*/  tx_stat_gt255 ; 
 int /*<<< orphan*/  tx_stat_gt4095 ; 
 int /*<<< orphan*/  tx_stat_gt511 ; 
 int /*<<< orphan*/  tx_stat_gt64 ; 
 int /*<<< orphan*/  tx_stat_gt9216 ; 
 int /*<<< orphan*/  tx_stat_gterr ; 
 int /*<<< orphan*/  tx_stat_gtufl ; 
 int /*<<< orphan*/  tx_stat_gtxpf ; 
 int /*<<< orphan*/  tx_stat_mac_16383 ; 
 int /*<<< orphan*/  tx_stat_mac_2047 ; 
 int /*<<< orphan*/  tx_stat_mac_4095 ; 
 int /*<<< orphan*/  tx_stat_mac_9216 ; 
 int /*<<< orphan*/  tx_stat_mac_ufl ; 
 int /*<<< orphan*/  tx_stat_outxoffsent ; 

__attribute__((used)) static void
bxe_bmac_stats_update(struct bxe_softc *sc)
{
    struct host_port_stats *pstats = BXE_SP(sc, port_stats);
    struct bxe_eth_stats *estats = &sc->eth_stats;
    struct {
        uint32_t lo;
        uint32_t hi;
    } diff;

    if (CHIP_IS_E1x(sc)) {
        struct bmac1_stats *new = BXE_SP(sc, mac_stats.bmac1_stats);

        /* the macros below will use "bmac1_stats" type */
        UPDATE_STAT64(rx_stat_grerb, rx_stat_ifhcinbadoctets);
        UPDATE_STAT64(rx_stat_grfcs, rx_stat_dot3statsfcserrors);
        UPDATE_STAT64(rx_stat_grund, rx_stat_etherstatsundersizepkts);
        UPDATE_STAT64(rx_stat_grovr, rx_stat_dot3statsframestoolong);
        UPDATE_STAT64(rx_stat_grfrg, rx_stat_etherstatsfragments);
        UPDATE_STAT64(rx_stat_grjbr, rx_stat_etherstatsjabbers);
        UPDATE_STAT64(rx_stat_grxcf, rx_stat_maccontrolframesreceived);
        UPDATE_STAT64(rx_stat_grxpf, rx_stat_xoffstateentered);
        UPDATE_STAT64(rx_stat_grxpf, rx_stat_mac_xpf);

        UPDATE_STAT64(tx_stat_gtxpf, tx_stat_outxoffsent);
        UPDATE_STAT64(tx_stat_gtxpf, tx_stat_flowcontroldone);
        UPDATE_STAT64(tx_stat_gt64, tx_stat_etherstatspkts64octets);
        UPDATE_STAT64(tx_stat_gt127,
                      tx_stat_etherstatspkts65octetsto127octets);
        UPDATE_STAT64(tx_stat_gt255,
                      tx_stat_etherstatspkts128octetsto255octets);
        UPDATE_STAT64(tx_stat_gt511,
                      tx_stat_etherstatspkts256octetsto511octets);
        UPDATE_STAT64(tx_stat_gt1023,
                      tx_stat_etherstatspkts512octetsto1023octets);
        UPDATE_STAT64(tx_stat_gt1518,
                      tx_stat_etherstatspkts1024octetsto1522octets);
        UPDATE_STAT64(tx_stat_gt2047, tx_stat_mac_2047);
        UPDATE_STAT64(tx_stat_gt4095, tx_stat_mac_4095);
        UPDATE_STAT64(tx_stat_gt9216, tx_stat_mac_9216);
        UPDATE_STAT64(tx_stat_gt16383, tx_stat_mac_16383);
        UPDATE_STAT64(tx_stat_gterr,
                      tx_stat_dot3statsinternalmactransmiterrors);
        UPDATE_STAT64(tx_stat_gtufl, tx_stat_mac_ufl);
    } else {
        struct bmac2_stats *new = BXE_SP(sc, mac_stats.bmac2_stats);
        struct bxe_fw_port_stats_old *fwstats = &sc->fw_stats_old;

        /* the macros below will use "bmac2_stats" type */
        UPDATE_STAT64(rx_stat_grerb, rx_stat_ifhcinbadoctets);
        UPDATE_STAT64(rx_stat_grfcs, rx_stat_dot3statsfcserrors);
        UPDATE_STAT64(rx_stat_grund, rx_stat_etherstatsundersizepkts);
        UPDATE_STAT64(rx_stat_grovr, rx_stat_dot3statsframestoolong);
        UPDATE_STAT64(rx_stat_grfrg, rx_stat_etherstatsfragments);
        UPDATE_STAT64(rx_stat_grjbr, rx_stat_etherstatsjabbers);
        UPDATE_STAT64(rx_stat_grxcf, rx_stat_maccontrolframesreceived);
        UPDATE_STAT64(rx_stat_grxpf, rx_stat_xoffstateentered);
        UPDATE_STAT64(rx_stat_grxpf, rx_stat_mac_xpf);
        UPDATE_STAT64(tx_stat_gtxpf, tx_stat_outxoffsent);
        UPDATE_STAT64(tx_stat_gtxpf, tx_stat_flowcontroldone);
        UPDATE_STAT64(tx_stat_gt64, tx_stat_etherstatspkts64octets);
        UPDATE_STAT64(tx_stat_gt127,
                      tx_stat_etherstatspkts65octetsto127octets);
        UPDATE_STAT64(tx_stat_gt255,
                      tx_stat_etherstatspkts128octetsto255octets);
        UPDATE_STAT64(tx_stat_gt511,
                      tx_stat_etherstatspkts256octetsto511octets);
        UPDATE_STAT64(tx_stat_gt1023,
                      tx_stat_etherstatspkts512octetsto1023octets);
        UPDATE_STAT64(tx_stat_gt1518,
                      tx_stat_etherstatspkts1024octetsto1522octets);
        UPDATE_STAT64(tx_stat_gt2047, tx_stat_mac_2047);
        UPDATE_STAT64(tx_stat_gt4095, tx_stat_mac_4095);
        UPDATE_STAT64(tx_stat_gt9216, tx_stat_mac_9216);
        UPDATE_STAT64(tx_stat_gt16383, tx_stat_mac_16383);
        UPDATE_STAT64(tx_stat_gterr,
                      tx_stat_dot3statsinternalmactransmiterrors);
        UPDATE_STAT64(tx_stat_gtufl, tx_stat_mac_ufl);

        /* collect PFC stats */
        pstats->pfc_frames_tx_hi = new->tx_stat_gtpp_hi;
        pstats->pfc_frames_tx_lo = new->tx_stat_gtpp_lo;
        ADD_64(pstats->pfc_frames_tx_hi, fwstats->pfc_frames_tx_hi,
               pstats->pfc_frames_tx_lo, fwstats->pfc_frames_tx_lo);

        pstats->pfc_frames_rx_hi = new->rx_stat_grpp_hi;
        pstats->pfc_frames_rx_lo = new->rx_stat_grpp_lo;
        ADD_64(pstats->pfc_frames_rx_hi, fwstats->pfc_frames_rx_hi,
               pstats->pfc_frames_rx_lo, fwstats->pfc_frames_rx_lo);
    }

    estats->pause_frames_received_hi = pstats->mac_stx[1].rx_stat_mac_xpf_hi;
    estats->pause_frames_received_lo = pstats->mac_stx[1].rx_stat_mac_xpf_lo;

    estats->pause_frames_sent_hi = pstats->mac_stx[1].tx_stat_outxoffsent_hi;
    estats->pause_frames_sent_lo = pstats->mac_stx[1].tx_stat_outxoffsent_lo;

    estats->pfc_frames_received_hi = pstats->pfc_frames_rx_hi;
    estats->pfc_frames_received_lo = pstats->pfc_frames_rx_lo;
    estats->pfc_frames_sent_hi = pstats->pfc_frames_tx_hi;
    estats->pfc_frames_sent_lo = pstats->pfc_frames_tx_lo;
}