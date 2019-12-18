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
struct host_port_stats {TYPE_1__* mac_stx; } ;
struct emac_stats {int dummy; } ;
struct bxe_eth_stats {int /*<<< orphan*/  pause_frames_sent_lo; int /*<<< orphan*/  pause_frames_sent_hi; int /*<<< orphan*/  pause_frames_received_lo; int /*<<< orphan*/  pause_frames_received_hi; } ;
struct bxe_softc {struct bxe_eth_stats eth_stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  emac_stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_stat_outxoffsent_lo; int /*<<< orphan*/  tx_stat_outxoffsent_hi; int /*<<< orphan*/  tx_stat_outxonsent_lo; int /*<<< orphan*/  tx_stat_outxonsent_hi; int /*<<< orphan*/  rx_stat_xoffpauseframesreceived_lo; int /*<<< orphan*/  rx_stat_xoffpauseframesreceived_hi; int /*<<< orphan*/  rx_stat_xonpauseframesreceived_lo; int /*<<< orphan*/  rx_stat_xonpauseframesreceived_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_EXTEND_STAT (int /*<<< orphan*/ ) ; 
 TYPE_2__ mac_stats ; 
 int /*<<< orphan*/  port_stats ; 
 int /*<<< orphan*/  rx_stat_dot3statsalignmenterrors ; 
 int /*<<< orphan*/  rx_stat_dot3statscarriersenseerrors ; 
 int /*<<< orphan*/  rx_stat_dot3statsfcserrors ; 
 int /*<<< orphan*/  rx_stat_dot3statsframestoolong ; 
 int /*<<< orphan*/  rx_stat_etherstatsfragments ; 
 int /*<<< orphan*/  rx_stat_etherstatsjabbers ; 
 int /*<<< orphan*/  rx_stat_etherstatsundersizepkts ; 
 int /*<<< orphan*/  rx_stat_falsecarriererrors ; 
 int /*<<< orphan*/  rx_stat_ifhcinbadoctets ; 
 int /*<<< orphan*/  rx_stat_maccontrolframesreceived ; 
 int /*<<< orphan*/  rx_stat_xoffpauseframesreceived ; 
 int /*<<< orphan*/  rx_stat_xoffstateentered ; 
 int /*<<< orphan*/  rx_stat_xonpauseframesreceived ; 
 int /*<<< orphan*/  tx_stat_dot3statsdeferredtransmissions ; 
 int /*<<< orphan*/  tx_stat_dot3statsexcessivecollisions ; 
 int /*<<< orphan*/  tx_stat_dot3statsinternalmactransmiterrors ; 
 int /*<<< orphan*/  tx_stat_dot3statslatecollisions ; 
 int /*<<< orphan*/  tx_stat_dot3statsmultiplecollisionframes ; 
 int /*<<< orphan*/  tx_stat_dot3statssinglecollisionframes ; 
 int /*<<< orphan*/  tx_stat_etherstatscollisions ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts1024octetsto1522octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts128octetsto255octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts256octetsto511octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts512octetsto1023octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts64octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspkts65octetsto127octets ; 
 int /*<<< orphan*/  tx_stat_etherstatspktsover1522octets ; 
 int /*<<< orphan*/  tx_stat_flowcontroldone ; 
 int /*<<< orphan*/  tx_stat_ifhcoutbadoctets ; 
 int /*<<< orphan*/  tx_stat_outxoffsent ; 
 int /*<<< orphan*/  tx_stat_outxonsent ; 

__attribute__((used)) static void
bxe_emac_stats_update(struct bxe_softc *sc)
{
    struct emac_stats *new = BXE_SP(sc, mac_stats.emac_stats);
    struct host_port_stats *pstats = BXE_SP(sc, port_stats);
    struct bxe_eth_stats *estats = &sc->eth_stats;

    UPDATE_EXTEND_STAT(rx_stat_ifhcinbadoctets);
    UPDATE_EXTEND_STAT(tx_stat_ifhcoutbadoctets);
    UPDATE_EXTEND_STAT(rx_stat_dot3statsfcserrors);
    UPDATE_EXTEND_STAT(rx_stat_dot3statsalignmenterrors);
    UPDATE_EXTEND_STAT(rx_stat_dot3statscarriersenseerrors);
    UPDATE_EXTEND_STAT(rx_stat_falsecarriererrors);
    UPDATE_EXTEND_STAT(rx_stat_etherstatsundersizepkts);
    UPDATE_EXTEND_STAT(rx_stat_dot3statsframestoolong);
    UPDATE_EXTEND_STAT(rx_stat_etherstatsfragments);
    UPDATE_EXTEND_STAT(rx_stat_etherstatsjabbers);
    UPDATE_EXTEND_STAT(rx_stat_maccontrolframesreceived);
    UPDATE_EXTEND_STAT(rx_stat_xoffstateentered);
    UPDATE_EXTEND_STAT(rx_stat_xonpauseframesreceived);
    UPDATE_EXTEND_STAT(rx_stat_xoffpauseframesreceived);
    UPDATE_EXTEND_STAT(tx_stat_outxonsent);
    UPDATE_EXTEND_STAT(tx_stat_outxoffsent);
    UPDATE_EXTEND_STAT(tx_stat_flowcontroldone);
    UPDATE_EXTEND_STAT(tx_stat_etherstatscollisions);
    UPDATE_EXTEND_STAT(tx_stat_dot3statssinglecollisionframes);
    UPDATE_EXTEND_STAT(tx_stat_dot3statsmultiplecollisionframes);
    UPDATE_EXTEND_STAT(tx_stat_dot3statsdeferredtransmissions);
    UPDATE_EXTEND_STAT(tx_stat_dot3statsexcessivecollisions);
    UPDATE_EXTEND_STAT(tx_stat_dot3statslatecollisions);
    UPDATE_EXTEND_STAT(tx_stat_etherstatspkts64octets);
    UPDATE_EXTEND_STAT(tx_stat_etherstatspkts65octetsto127octets);
    UPDATE_EXTEND_STAT(tx_stat_etherstatspkts128octetsto255octets);
    UPDATE_EXTEND_STAT(tx_stat_etherstatspkts256octetsto511octets);
    UPDATE_EXTEND_STAT(tx_stat_etherstatspkts512octetsto1023octets);
    UPDATE_EXTEND_STAT(tx_stat_etherstatspkts1024octetsto1522octets);
    UPDATE_EXTEND_STAT(tx_stat_etherstatspktsover1522octets);
    UPDATE_EXTEND_STAT(tx_stat_dot3statsinternalmactransmiterrors);

    estats->pause_frames_received_hi =
        pstats->mac_stx[1].rx_stat_xonpauseframesreceived_hi;
    estats->pause_frames_received_lo =
        pstats->mac_stx[1].rx_stat_xonpauseframesreceived_lo;
    ADD_64(estats->pause_frames_received_hi,
           pstats->mac_stx[1].rx_stat_xoffpauseframesreceived_hi,
           estats->pause_frames_received_lo,
           pstats->mac_stx[1].rx_stat_xoffpauseframesreceived_lo);

    estats->pause_frames_sent_hi =
        pstats->mac_stx[1].tx_stat_outxonsent_hi;
    estats->pause_frames_sent_lo =
        pstats->mac_stx[1].tx_stat_outxonsent_lo;
    ADD_64(estats->pause_frames_sent_hi,
           pstats->mac_stx[1].tx_stat_outxoffsent_hi,
           estats->pause_frames_sent_lo,
           pstats->mac_stx[1].tx_stat_outxoffsent_lo);
}