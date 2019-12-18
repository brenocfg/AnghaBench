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
typedef  int /*<<< orphan*/  uint32_t ;
struct xstorm_per_queue_stats {int /*<<< orphan*/  ucast_bytes_sent; int /*<<< orphan*/  mcast_bytes_sent; int /*<<< orphan*/  bcast_bytes_sent; int /*<<< orphan*/  mcast_pkts_sent; int /*<<< orphan*/  bcast_pkts_sent; int /*<<< orphan*/  ucast_pkts_sent; } ;
struct ustorm_per_queue_stats {int /*<<< orphan*/  coalesced_bytes; } ;
struct tstorm_per_queue_stats {int /*<<< orphan*/  rcv_ucast_bytes; int /*<<< orphan*/  rcv_mcast_bytes; int /*<<< orphan*/  rcv_bcast_bytes; } ;
struct tstorm_per_port_stats {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct tstorm_per_pf_stats {TYPE_1__ rcv_error_bytes; } ;
struct host_func_stats {scalar_t__ host_func_stats_end; scalar_t__ host_func_stats_start; } ;
struct bxe_fw_port_stats_old {int dummy; } ;
struct TYPE_8__ {scalar_t__ pmf; } ;
struct bxe_eth_stats_old {int dummy; } ;
struct bxe_eth_stats {int /*<<< orphan*/  rx_stat_ifhcinbadoctets_lo; scalar_t__ error_bytes_received_lo; int /*<<< orphan*/  rx_stat_ifhcinbadoctets_hi; scalar_t__ error_bytes_received_hi; scalar_t__ total_bytes_received_lo; scalar_t__ total_bytes_received_hi; } ;
struct bxe_softc {int num_queues; scalar_t__ stats_pending; struct bxe_fw_port_stats_old fw_stats_old; TYPE_2__ port; TYPE_6__* fw_stats_data; struct bxe_fastpath* fp; struct bxe_eth_stats_old eth_stats_old; struct bxe_eth_stats eth_stats; struct host_func_stats func_stats; } ;
struct bxe_eth_q_stats_old {int dummy; } ;
struct bxe_eth_q_stats {int /*<<< orphan*/  total_multicast_bytes_transmitted_lo; scalar_t__ total_bytes_transmitted_lo; int /*<<< orphan*/  total_multicast_bytes_transmitted_hi; scalar_t__ total_bytes_transmitted_hi; int /*<<< orphan*/  total_broadcast_bytes_transmitted_lo; int /*<<< orphan*/  total_broadcast_bytes_transmitted_hi; scalar_t__ total_unicast_bytes_transmitted_lo; scalar_t__ total_unicast_bytes_transmitted_hi; scalar_t__ total_bytes_received_lo; scalar_t__ valid_bytes_received_lo; scalar_t__ total_bytes_received_hi; scalar_t__ valid_bytes_received_hi; int /*<<< orphan*/  total_unicast_bytes_received_lo; int /*<<< orphan*/  total_unicast_bytes_received_hi; int /*<<< orphan*/  total_multicast_bytes_received_lo; int /*<<< orphan*/  total_multicast_bytes_received_hi; scalar_t__ total_broadcast_bytes_received_lo; scalar_t__ total_broadcast_bytes_received_hi; } ;
struct bxe_fastpath {struct bxe_eth_q_stats_old eth_q_stats_old; struct bxe_eth_q_stats eth_q_stats; struct xstorm_per_queue_stats old_xclient; struct ustorm_per_queue_stats old_uclient; struct tstorm_per_queue_stats old_tclient; } ;
struct TYPE_10__ {struct tstorm_per_pf_stats tstorm_pf_statistics; } ;
struct TYPE_9__ {struct tstorm_per_port_stats tstorm_port_statistics; } ;
struct TYPE_12__ {TYPE_5__* queue_stats; TYPE_4__ pf; TYPE_3__ port; } ;
struct TYPE_11__ {struct xstorm_per_queue_stats xstorm_queue_statistics; struct ustorm_per_queue_stats ustorm_queue_statistics; struct tstorm_per_queue_stats tstorm_queue_statistics; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_64 (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_64_LE (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DBG_STATS ; 
 int EAGAIN ; 
 scalar_t__ IS_PF (struct bxe_softc*) ; 
 int /*<<< orphan*/  SUB_EXTEND_USTAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_ESTAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_ESTAT_QSTAT_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_EXTEND_E_TSTAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UPDATE_EXTEND_E_USTAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_EXTEND_TSTAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_EXTEND_XSTAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_FSTAT_QSTAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_FW_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_QSTAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcast_no_buff_pkts ; 
 int /*<<< orphan*/  bcast_pkts_sent ; 
 int /*<<< orphan*/  brb_truncate_discard ; 
 scalar_t__ bxe_storm_stats_validate_counters (struct bxe_softc*) ; 
 int /*<<< orphan*/  checksum_discard ; 
 int /*<<< orphan*/  coalesced_events ; 
 int /*<<< orphan*/  coalesced_pkts ; 
 int /*<<< orphan*/  error_drop_pkts ; 
 int /*<<< orphan*/  etherstatsoverrsizepkts ; 
 int /*<<< orphan*/  mac_discard ; 
 int /*<<< orphan*/  mac_filter_discard ; 
 int /*<<< orphan*/  mcast_no_buff_pkts ; 
 int /*<<< orphan*/  mcast_pkts_sent ; 
 int /*<<< orphan*/  mf_tag_discard ; 
 int /*<<< orphan*/  no_buff_discard ; 
 int /*<<< orphan*/  pkts_too_big_discard ; 
 int /*<<< orphan*/  rcv_bcast_pkts ; 
 int /*<<< orphan*/  rcv_mcast_pkts ; 
 int /*<<< orphan*/  rcv_ucast_pkts ; 
 int /*<<< orphan*/  rx_stat_dot3statsframestoolong ; 
 int /*<<< orphan*/  total_broadcast_bytes_received ; 
 int /*<<< orphan*/  total_broadcast_bytes_transmitted ; 
 int /*<<< orphan*/  total_broadcast_packets_received ; 
 int /*<<< orphan*/  total_broadcast_packets_transmitted ; 
 int /*<<< orphan*/  total_bytes_received ; 
 int /*<<< orphan*/  total_bytes_transmitted ; 
 int /*<<< orphan*/  total_multicast_bytes_received ; 
 int /*<<< orphan*/  total_multicast_bytes_transmitted ; 
 int /*<<< orphan*/  total_multicast_packets_received ; 
 int /*<<< orphan*/  total_multicast_packets_transmitted ; 
 int /*<<< orphan*/  total_packets_received_checksum_discarded ; 
 int /*<<< orphan*/  total_packets_received_ttl0_discarded ; 
 int /*<<< orphan*/  total_tpa_aggregated_frames ; 
 int /*<<< orphan*/  total_tpa_aggregations ; 
 int /*<<< orphan*/  total_tpa_bytes ; 
 int /*<<< orphan*/  total_transmitted_dropped_packets_error ; 
 int /*<<< orphan*/  total_unicast_bytes_received ; 
 int /*<<< orphan*/  total_unicast_bytes_transmitted ; 
 int /*<<< orphan*/  total_unicast_packets_received ; 
 int /*<<< orphan*/  total_unicast_packets_transmitted ; 
 int /*<<< orphan*/  ttl0_discard ; 
 int /*<<< orphan*/  ucast_no_buff_pkts ; 
 int /*<<< orphan*/  ucast_pkts_sent ; 
 int /*<<< orphan*/  valid_bytes_received ; 

__attribute__((used)) static int
bxe_storm_stats_update(struct bxe_softc *sc)
{
    struct tstorm_per_port_stats *tport =
        &sc->fw_stats_data->port.tstorm_port_statistics;
    struct tstorm_per_pf_stats *tfunc =
        &sc->fw_stats_data->pf.tstorm_pf_statistics;
    struct host_func_stats *fstats = &sc->func_stats;
    struct bxe_eth_stats *estats = &sc->eth_stats;
    struct bxe_eth_stats_old *estats_old = &sc->eth_stats_old;
    int i;

    /* vfs stat counter is managed by pf */
    if (IS_PF(sc) && bxe_storm_stats_validate_counters(sc)) {
        return (-EAGAIN);
    }

    estats->error_bytes_received_hi = 0;
    estats->error_bytes_received_lo = 0;

    for (i = 0; i < sc->num_queues; i++) {
        struct bxe_fastpath *fp = &sc->fp[i];
        struct tstorm_per_queue_stats *tclient =
            &sc->fw_stats_data->queue_stats[i].tstorm_queue_statistics;
        struct tstorm_per_queue_stats *old_tclient = &fp->old_tclient;
        struct ustorm_per_queue_stats *uclient =
            &sc->fw_stats_data->queue_stats[i].ustorm_queue_statistics;
        struct ustorm_per_queue_stats *old_uclient = &fp->old_uclient;
        struct xstorm_per_queue_stats *xclient =
            &sc->fw_stats_data->queue_stats[i].xstorm_queue_statistics;
        struct xstorm_per_queue_stats *old_xclient = &fp->old_xclient;
        struct bxe_eth_q_stats *qstats = &fp->eth_q_stats;
        struct bxe_eth_q_stats_old *qstats_old = &fp->eth_q_stats_old;

        uint32_t diff;

        BLOGD(sc, DBG_STATS,
              "queue[%d]: ucast_sent 0x%x bcast_sent 0x%x mcast_sent 0x%x\n",
              i, xclient->ucast_pkts_sent, xclient->bcast_pkts_sent,
              xclient->mcast_pkts_sent);

        BLOGD(sc, DBG_STATS, "---------------\n");

        UPDATE_QSTAT(tclient->rcv_bcast_bytes,
                     total_broadcast_bytes_received);
        UPDATE_QSTAT(tclient->rcv_mcast_bytes,
                     total_multicast_bytes_received);
        UPDATE_QSTAT(tclient->rcv_ucast_bytes,
                     total_unicast_bytes_received);

        /*
         * sum to total_bytes_received all
         * unicast/multicast/broadcast
         */
        qstats->total_bytes_received_hi =
            qstats->total_broadcast_bytes_received_hi;
        qstats->total_bytes_received_lo =
            qstats->total_broadcast_bytes_received_lo;

        ADD_64(qstats->total_bytes_received_hi,
               qstats->total_multicast_bytes_received_hi,
               qstats->total_bytes_received_lo,
               qstats->total_multicast_bytes_received_lo);

        ADD_64(qstats->total_bytes_received_hi,
               qstats->total_unicast_bytes_received_hi,
               qstats->total_bytes_received_lo,
               qstats->total_unicast_bytes_received_lo);

        qstats->valid_bytes_received_hi = qstats->total_bytes_received_hi;
        qstats->valid_bytes_received_lo = qstats->total_bytes_received_lo;

        UPDATE_EXTEND_TSTAT(rcv_ucast_pkts, total_unicast_packets_received);
        UPDATE_EXTEND_TSTAT(rcv_mcast_pkts, total_multicast_packets_received);
        UPDATE_EXTEND_TSTAT(rcv_bcast_pkts, total_broadcast_packets_received);
        UPDATE_EXTEND_E_TSTAT(pkts_too_big_discard,
                              etherstatsoverrsizepkts, 32);
        UPDATE_EXTEND_E_TSTAT(no_buff_discard, no_buff_discard, 16);

        SUB_EXTEND_USTAT(ucast_no_buff_pkts, total_unicast_packets_received);
        SUB_EXTEND_USTAT(mcast_no_buff_pkts,
                         total_multicast_packets_received);
        SUB_EXTEND_USTAT(bcast_no_buff_pkts,
                         total_broadcast_packets_received);
        UPDATE_EXTEND_E_USTAT(ucast_no_buff_pkts, no_buff_discard);
        UPDATE_EXTEND_E_USTAT(mcast_no_buff_pkts, no_buff_discard);
        UPDATE_EXTEND_E_USTAT(bcast_no_buff_pkts, no_buff_discard);

        UPDATE_QSTAT(xclient->bcast_bytes_sent,
                     total_broadcast_bytes_transmitted);
        UPDATE_QSTAT(xclient->mcast_bytes_sent,
                     total_multicast_bytes_transmitted);
        UPDATE_QSTAT(xclient->ucast_bytes_sent,
                     total_unicast_bytes_transmitted);

        /*
         * sum to total_bytes_transmitted all
         * unicast/multicast/broadcast
         */
        qstats->total_bytes_transmitted_hi =
            qstats->total_unicast_bytes_transmitted_hi;
        qstats->total_bytes_transmitted_lo =
            qstats->total_unicast_bytes_transmitted_lo;

        ADD_64(qstats->total_bytes_transmitted_hi,
               qstats->total_broadcast_bytes_transmitted_hi,
               qstats->total_bytes_transmitted_lo,
               qstats->total_broadcast_bytes_transmitted_lo);

        ADD_64(qstats->total_bytes_transmitted_hi,
               qstats->total_multicast_bytes_transmitted_hi,
               qstats->total_bytes_transmitted_lo,
               qstats->total_multicast_bytes_transmitted_lo);

        UPDATE_EXTEND_XSTAT(ucast_pkts_sent,
                            total_unicast_packets_transmitted);
        UPDATE_EXTEND_XSTAT(mcast_pkts_sent,
                            total_multicast_packets_transmitted);
        UPDATE_EXTEND_XSTAT(bcast_pkts_sent,
                            total_broadcast_packets_transmitted);

        UPDATE_EXTEND_TSTAT(checksum_discard,
                            total_packets_received_checksum_discarded);
        UPDATE_EXTEND_TSTAT(ttl0_discard,
                            total_packets_received_ttl0_discarded);

        UPDATE_EXTEND_XSTAT(error_drop_pkts,
                            total_transmitted_dropped_packets_error);

        /* TPA aggregations completed */
        UPDATE_EXTEND_E_USTAT(coalesced_events, total_tpa_aggregations);
        /* Number of network frames aggregated by TPA */
        UPDATE_EXTEND_E_USTAT(coalesced_pkts, total_tpa_aggregated_frames);
        /* Total number of bytes in completed TPA aggregations */
        UPDATE_QSTAT(uclient->coalesced_bytes, total_tpa_bytes);

        UPDATE_ESTAT_QSTAT_64(total_tpa_bytes);

        UPDATE_FSTAT_QSTAT(total_bytes_received);
        UPDATE_FSTAT_QSTAT(total_bytes_transmitted);
        UPDATE_FSTAT_QSTAT(total_unicast_packets_received);
        UPDATE_FSTAT_QSTAT(total_multicast_packets_received);
        UPDATE_FSTAT_QSTAT(total_broadcast_packets_received);
        UPDATE_FSTAT_QSTAT(total_unicast_packets_transmitted);
        UPDATE_FSTAT_QSTAT(total_multicast_packets_transmitted);
        UPDATE_FSTAT_QSTAT(total_broadcast_packets_transmitted);
        UPDATE_FSTAT_QSTAT(valid_bytes_received);
    }

    ADD_64(estats->total_bytes_received_hi,
           estats->rx_stat_ifhcinbadoctets_hi,
           estats->total_bytes_received_lo,
           estats->rx_stat_ifhcinbadoctets_lo);

    ADD_64_LE(estats->total_bytes_received_hi,
              tfunc->rcv_error_bytes.hi,
              estats->total_bytes_received_lo,
              tfunc->rcv_error_bytes.lo);

    ADD_64_LE(estats->error_bytes_received_hi,
              tfunc->rcv_error_bytes.hi,
              estats->error_bytes_received_lo,
              tfunc->rcv_error_bytes.lo);

    UPDATE_ESTAT(etherstatsoverrsizepkts, rx_stat_dot3statsframestoolong);

    ADD_64(estats->error_bytes_received_hi,
           estats->rx_stat_ifhcinbadoctets_hi,
           estats->error_bytes_received_lo,
           estats->rx_stat_ifhcinbadoctets_lo);

    if (sc->port.pmf) {
        struct bxe_fw_port_stats_old *fwstats = &sc->fw_stats_old;
        UPDATE_FW_STAT(mac_filter_discard);
        UPDATE_FW_STAT(mf_tag_discard);
        UPDATE_FW_STAT(brb_truncate_discard);
        UPDATE_FW_STAT(mac_discard);
    }

    fstats->host_func_stats_start = ++fstats->host_func_stats_end;

    sc->stats_pending = 0;

    return (0);
}