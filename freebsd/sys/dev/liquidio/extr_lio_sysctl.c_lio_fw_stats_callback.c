#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct octeon_tx_stats {int /*<<< orphan*/  fw_tx_vxlan; int /*<<< orphan*/  fw_err_tso; int /*<<< orphan*/  fw_tso_fwd; int /*<<< orphan*/  fw_tso; int /*<<< orphan*/  fw_err_drop; int /*<<< orphan*/  fw_err_link; int /*<<< orphan*/  fw_err_pki; int /*<<< orphan*/  fw_err_pko; int /*<<< orphan*/  fw_total_fwd; int /*<<< orphan*/  fw_total_sent; int /*<<< orphan*/  total_collisions; int /*<<< orphan*/  runts; int /*<<< orphan*/  fifo_err; int /*<<< orphan*/  max_deferral_fail; int /*<<< orphan*/  max_collision_fail; int /*<<< orphan*/  multi_collision_sent; int /*<<< orphan*/  one_collision_sent; int /*<<< orphan*/  ctl_sent; int /*<<< orphan*/  bcast_pkts_sent; int /*<<< orphan*/  mcast_pkts_sent; int /*<<< orphan*/  total_bytes_sent; int /*<<< orphan*/  total_pkts_sent; } ;
struct octeon_rx_stats {int /*<<< orphan*/  fwd_rate; int /*<<< orphan*/  fw_lro_aborts_timer; int /*<<< orphan*/  fw_lro_aborts_tsval; int /*<<< orphan*/  fw_lro_aborts_seq; int /*<<< orphan*/  fw_lro_aborts_port; int /*<<< orphan*/  fw_lro_aborts; int /*<<< orphan*/  fw_total_lro; int /*<<< orphan*/  fw_lro_octs; int /*<<< orphan*/  fw_lro_pkts; int /*<<< orphan*/  fw_rx_vxlan_err; int /*<<< orphan*/  fw_rx_vxlan; int /*<<< orphan*/  fw_err_drop; int /*<<< orphan*/  fw_err_link; int /*<<< orphan*/  fw_err_pko; int /*<<< orphan*/  fw_total_fwd; int /*<<< orphan*/  fw_total_rcvd; int /*<<< orphan*/  frame_err; int /*<<< orphan*/  l2_err; int /*<<< orphan*/  jabber_err; int /*<<< orphan*/  fcs_err; int /*<<< orphan*/  dmac_drop; int /*<<< orphan*/  fifo_err; int /*<<< orphan*/  ctl_rcvd; int /*<<< orphan*/  runts; int /*<<< orphan*/  total_mcst; int /*<<< orphan*/  total_bcst; int /*<<< orphan*/  bytes_rcvd; int /*<<< orphan*/  total_rcvd; } ;
struct octeon_link_stats {int dummy; } ;
struct TYPE_5__ {struct ifnet* ifp; } ;
struct TYPE_4__ {struct octeon_tx_stats fromhost; struct octeon_rx_stats fromwire; } ;
struct octeon_device {TYPE_2__ props; TYPE_1__ link_stats; } ;
struct lio_soft_command {scalar_t__ virtrptr; } ;
struct TYPE_6__ {struct octeon_tx_stats fromhost; struct octeon_rx_stats fromwire; } ;
struct lio_fw_stats_resp {TYPE_3__ stats; int /*<<< orphan*/  status; } ;
struct lio {int /*<<< orphan*/  stats_interval; int /*<<< orphan*/  stats_timer; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ LIO_REQUEST_TIMEOUT ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct lio* if_getsoftc (struct ifnet*) ; 
 int /*<<< orphan*/  lio_free_soft_command (struct octeon_device*,struct lio_soft_command*) ; 
 int /*<<< orphan*/  lio_ms_to_ticks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_swap_8B_data (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
lio_fw_stats_callback(struct octeon_device *oct_dev, uint32_t status, void *ptr)
{
	struct lio_soft_command	*sc = (struct lio_soft_command *)ptr;
	struct lio_fw_stats_resp *resp =
		(struct lio_fw_stats_resp *)sc->virtrptr;
	struct octeon_rx_stats	*rsp_rstats = &resp->stats.fromwire;
	struct octeon_tx_stats	*rsp_tstats = &resp->stats.fromhost;
	struct octeon_rx_stats	*rstats = &oct_dev->link_stats.fromwire;
	struct octeon_tx_stats	*tstats = &oct_dev->link_stats.fromhost;
	struct ifnet		*ifp = oct_dev->props.ifp;
	struct lio		*lio = if_getsoftc(ifp);

	if ((status != LIO_REQUEST_TIMEOUT) && !resp->status) {
		lio_swap_8B_data((uint64_t *)&resp->stats,
				 (sizeof(struct octeon_link_stats)) >> 3);

		/* RX link-level stats */
		rstats->total_rcvd = rsp_rstats->total_rcvd;
		rstats->bytes_rcvd = rsp_rstats->bytes_rcvd;
		rstats->total_bcst = rsp_rstats->total_bcst;
		rstats->total_mcst = rsp_rstats->total_mcst;
		rstats->runts = rsp_rstats->runts;
		rstats->ctl_rcvd = rsp_rstats->ctl_rcvd;
		/* Accounts for over/under-run of buffers */
		rstats->fifo_err = rsp_rstats->fifo_err;
		rstats->dmac_drop = rsp_rstats->dmac_drop;
		rstats->fcs_err = rsp_rstats->fcs_err;
		rstats->jabber_err = rsp_rstats->jabber_err;
		rstats->l2_err = rsp_rstats->l2_err;
		rstats->frame_err = rsp_rstats->frame_err;

		/* RX firmware stats */
		rstats->fw_total_rcvd = rsp_rstats->fw_total_rcvd;
		rstats->fw_total_fwd = rsp_rstats->fw_total_fwd;
		rstats->fw_err_pko = rsp_rstats->fw_err_pko;
		rstats->fw_err_link = rsp_rstats->fw_err_link;
		rstats->fw_err_drop = rsp_rstats->fw_err_drop;
		rstats->fw_rx_vxlan = rsp_rstats->fw_rx_vxlan;
		rstats->fw_rx_vxlan_err = rsp_rstats->fw_rx_vxlan_err;

		/* Number of packets that are LROed      */
		rstats->fw_lro_pkts = rsp_rstats->fw_lro_pkts;
		/* Number of octets that are LROed       */
		rstats->fw_lro_octs = rsp_rstats->fw_lro_octs;
		/* Number of LRO packets formed          */
		rstats->fw_total_lro = rsp_rstats->fw_total_lro;
		/* Number of times lRO of packet aborted */
		rstats->fw_lro_aborts = rsp_rstats->fw_lro_aborts;
		rstats->fw_lro_aborts_port = rsp_rstats->fw_lro_aborts_port;
		rstats->fw_lro_aborts_seq = rsp_rstats->fw_lro_aborts_seq;
		rstats->fw_lro_aborts_tsval = rsp_rstats->fw_lro_aborts_tsval;
		rstats->fw_lro_aborts_timer = rsp_rstats->fw_lro_aborts_timer;
		/* intrmod: packet forward rate */
		rstats->fwd_rate = rsp_rstats->fwd_rate;

		/* TX link-level stats */
		tstats->total_pkts_sent = rsp_tstats->total_pkts_sent;
		tstats->total_bytes_sent = rsp_tstats->total_bytes_sent;
		tstats->mcast_pkts_sent = rsp_tstats->mcast_pkts_sent;
		tstats->bcast_pkts_sent = rsp_tstats->bcast_pkts_sent;
		tstats->ctl_sent = rsp_tstats->ctl_sent;
		/* Packets sent after one collision */
		tstats->one_collision_sent = rsp_tstats->one_collision_sent;
		/* Packets sent after multiple collision */
		tstats->multi_collision_sent = rsp_tstats->multi_collision_sent;
		/* Packets not sent due to max collisions */
		tstats->max_collision_fail = rsp_tstats->max_collision_fail;
		/* Packets not sent due to max deferrals */
		tstats->max_deferral_fail = rsp_tstats->max_deferral_fail;
		/* Accounts for over/under-run of buffers */
		tstats->fifo_err = rsp_tstats->fifo_err;
		tstats->runts = rsp_tstats->runts;
		/* Total number of collisions detected */
		tstats->total_collisions = rsp_tstats->total_collisions;

		/* firmware stats */
		tstats->fw_total_sent = rsp_tstats->fw_total_sent;
		tstats->fw_total_fwd = rsp_tstats->fw_total_fwd;
		tstats->fw_err_pko = rsp_tstats->fw_err_pko;
		tstats->fw_err_pki = rsp_tstats->fw_err_pki;
		tstats->fw_err_link = rsp_tstats->fw_err_link;
		tstats->fw_err_drop = rsp_tstats->fw_err_drop;
		tstats->fw_tso = rsp_tstats->fw_tso;
		tstats->fw_tso_fwd = rsp_tstats->fw_tso_fwd;
		tstats->fw_err_tso = rsp_tstats->fw_err_tso;
		tstats->fw_tx_vxlan = rsp_tstats->fw_tx_vxlan;
	}
	lio_free_soft_command(oct_dev, sc);
	callout_schedule(&lio->stats_timer,
			 lio_ms_to_ticks(lio->stats_interval));
}