#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_mac_ctrl_frames; int /*<<< orphan*/  tx_mac_bc_packets; int /*<<< orphan*/  tx_mac_mc_packets; int /*<<< orphan*/  tx_mac_uc_packets; int /*<<< orphan*/  tx_mac_bytes; int /*<<< orphan*/  rx_mac_frames_ok; int /*<<< orphan*/  rx_mac_bc_packets; int /*<<< orphan*/  rx_mac_mc_packets; int /*<<< orphan*/  rx_mac_uc_packets; int /*<<< orphan*/  rx_mac_bytes; int /*<<< orphan*/  brb_discards; int /*<<< orphan*/  brb_truncates; int /*<<< orphan*/  tx_pfc_frames; int /*<<< orphan*/  tx_pause_frames; int /*<<< orphan*/  tx_1024_to_1518_byte_packets; int /*<<< orphan*/  tx_512_to_1023_byte_packets; int /*<<< orphan*/  tx_256_to_511_byte_packets; int /*<<< orphan*/  tx_128_to_255_byte_packets; int /*<<< orphan*/  tx_65_to_127_byte_packets; int /*<<< orphan*/  tx_64_byte_packets; int /*<<< orphan*/  rx_fragments; int /*<<< orphan*/  rx_undersize_packets; int /*<<< orphan*/  rx_jabbers; int /*<<< orphan*/  rx_oversize_packets; int /*<<< orphan*/  rx_carrier_errors; int /*<<< orphan*/  rx_align_errors; int /*<<< orphan*/  rx_pfc_frames; int /*<<< orphan*/  rx_pause_frames; int /*<<< orphan*/  rx_mac_crtl_frames; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_1024_to_1518_byte_packets; int /*<<< orphan*/  rx_512_to_1023_byte_packets; int /*<<< orphan*/  rx_256_to_511_byte_packets; int /*<<< orphan*/  rx_128_to_255_byte_packets; int /*<<< orphan*/  rx_65_to_127_byte_packets; int /*<<< orphan*/  rx_64_byte_packets; int /*<<< orphan*/  tpa_coalesced_bytes; int /*<<< orphan*/  tpa_not_coalesced_pkts; int /*<<< orphan*/  tpa_aborts_num; int /*<<< orphan*/  tpa_coalesced_events; int /*<<< orphan*/  tpa_coalesced_pkts; int /*<<< orphan*/  tx_err_drop_pkts; int /*<<< orphan*/  tx_bcast_pkts; int /*<<< orphan*/  tx_mcast_pkts; int /*<<< orphan*/  tx_ucast_pkts; int /*<<< orphan*/  tx_bcast_bytes; int /*<<< orphan*/  tx_mcast_bytes; int /*<<< orphan*/  tx_ucast_bytes; int /*<<< orphan*/  mac_filter_discards; int /*<<< orphan*/  mftag_filter_discards; int /*<<< orphan*/  rx_bcast_pkts; int /*<<< orphan*/  rx_mcast_pkts; int /*<<< orphan*/  rx_ucast_pkts; int /*<<< orphan*/  rx_bcast_bytes; int /*<<< orphan*/  rx_mcast_bytes; int /*<<< orphan*/  rx_ucast_bytes; int /*<<< orphan*/  ttl0_discard; int /*<<< orphan*/  packet_too_big_discard; int /*<<< orphan*/  no_buff_discards; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_total_collisions; int /*<<< orphan*/  tx_lpi_entry_count; int /*<<< orphan*/  tx_9217_to_16383_byte_packets; int /*<<< orphan*/  tx_4096_to_9216_byte_packets; int /*<<< orphan*/  tx_2048_to_4095_byte_packets; int /*<<< orphan*/  tx_1519_to_2047_byte_packets; int /*<<< orphan*/  rx_9217_to_16383_byte_packets; int /*<<< orphan*/  rx_4096_to_9216_byte_packets; int /*<<< orphan*/  rx_2048_to_4095_byte_packets; int /*<<< orphan*/  rx_1519_to_2047_byte_packets; int /*<<< orphan*/  rx_1519_to_1522_byte_packets; } ;
struct TYPE_8__ {TYPE_2__ common; TYPE_1__ bb; } ;
struct TYPE_9__ {TYPE_3__ hw_stats; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_4__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_QUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qlnx_add_hw_stats_sysctls(qlnx_host_t *ha)
{
        struct sysctl_ctx_list	*ctx;
        struct sysctl_oid_list	*children;
	struct sysctl_oid	*ctx_oid;

        ctx = device_get_sysctl_ctx(ha->pci_dev);
	children = SYSCTL_CHILDREN(device_get_sysctl_tree(ha->pci_dev));

	ctx_oid = SYSCTL_ADD_NODE(ctx, children, OID_AUTO, "hwstat",
			CTLFLAG_RD, NULL, "hwstat");
        children = SYSCTL_CHILDREN(ctx_oid);

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "no_buff_discards",
                CTLFLAG_RD, &ha->hw_stats.common.no_buff_discards,
                "No. of packets discarded due to lack of buffer");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "packet_too_big_discard",
                CTLFLAG_RD, &ha->hw_stats.common.packet_too_big_discard,
                "No. of packets discarded because packet was too big");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "ttl0_discard",
                CTLFLAG_RD, &ha->hw_stats.common.ttl0_discard,
                "ttl0_discard");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_ucast_bytes",
                CTLFLAG_RD, &ha->hw_stats.common.rx_ucast_bytes,
                "rx_ucast_bytes");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_mcast_bytes",
                CTLFLAG_RD, &ha->hw_stats.common.rx_mcast_bytes,
                "rx_mcast_bytes");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_bcast_bytes",
                CTLFLAG_RD, &ha->hw_stats.common.rx_bcast_bytes,
                "rx_bcast_bytes");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_ucast_pkts",
                CTLFLAG_RD, &ha->hw_stats.common.rx_ucast_pkts,
                "rx_ucast_pkts");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_mcast_pkts",
                CTLFLAG_RD, &ha->hw_stats.common.rx_mcast_pkts,
                "rx_mcast_pkts");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_bcast_pkts",
                CTLFLAG_RD, &ha->hw_stats.common.rx_bcast_pkts,
                "rx_bcast_pkts");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "mftag_filter_discards",
                CTLFLAG_RD, &ha->hw_stats.common.mftag_filter_discards,
                "mftag_filter_discards");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "mac_filter_discards",
                CTLFLAG_RD, &ha->hw_stats.common.mac_filter_discards,
                "mac_filter_discards");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_ucast_bytes",
                CTLFLAG_RD, &ha->hw_stats.common.tx_ucast_bytes,
                "tx_ucast_bytes");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_mcast_bytes",
                CTLFLAG_RD, &ha->hw_stats.common.tx_mcast_bytes,
                "tx_mcast_bytes");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_bcast_bytes",
                CTLFLAG_RD, &ha->hw_stats.common.tx_bcast_bytes,
                "tx_bcast_bytes");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_ucast_pkts",
                CTLFLAG_RD, &ha->hw_stats.common.tx_ucast_pkts,
                "tx_ucast_pkts");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_mcast_pkts",
                CTLFLAG_RD, &ha->hw_stats.common.tx_mcast_pkts,
                "tx_mcast_pkts");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_bcast_pkts",
                CTLFLAG_RD, &ha->hw_stats.common.tx_bcast_pkts,
                "tx_bcast_pkts");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_err_drop_pkts",
                CTLFLAG_RD, &ha->hw_stats.common.tx_err_drop_pkts,
                "tx_err_drop_pkts");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tpa_coalesced_pkts",
                CTLFLAG_RD, &ha->hw_stats.common.tpa_coalesced_pkts,
                "tpa_coalesced_pkts");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tpa_coalesced_events",
                CTLFLAG_RD, &ha->hw_stats.common.tpa_coalesced_events,
                "tpa_coalesced_events");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tpa_aborts_num",
                CTLFLAG_RD, &ha->hw_stats.common.tpa_aborts_num,
                "tpa_aborts_num");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tpa_not_coalesced_pkts",
                CTLFLAG_RD, &ha->hw_stats.common.tpa_not_coalesced_pkts,
                "tpa_not_coalesced_pkts");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tpa_coalesced_bytes",
                CTLFLAG_RD, &ha->hw_stats.common.tpa_coalesced_bytes,
                "tpa_coalesced_bytes");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_64_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.common.rx_64_byte_packets,
                "rx_64_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_65_to_127_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.common.rx_65_to_127_byte_packets,
                "rx_65_to_127_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_128_to_255_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.common.rx_128_to_255_byte_packets,
                "rx_128_to_255_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_256_to_511_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.common.rx_256_to_511_byte_packets,
                "rx_256_to_511_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_512_to_1023_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.common.rx_512_to_1023_byte_packets,
                "rx_512_to_1023_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_1024_to_1518_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.common.rx_1024_to_1518_byte_packets,
                "rx_1024_to_1518_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_1519_to_1522_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.bb.rx_1519_to_1522_byte_packets,
                "rx_1519_to_1522_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_1523_to_2047_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.bb.rx_1519_to_2047_byte_packets,
                "rx_1523_to_2047_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_2048_to_4095_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.bb.rx_2048_to_4095_byte_packets,
                "rx_2048_to_4095_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_4096_to_9216_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.bb.rx_4096_to_9216_byte_packets,
                "rx_4096_to_9216_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_9217_to_16383_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.bb.rx_9217_to_16383_byte_packets,
                "rx_9217_to_16383_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_crc_errors",
                CTLFLAG_RD, &ha->hw_stats.common.rx_crc_errors,
                "rx_crc_errors");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_mac_crtl_frames",
                CTLFLAG_RD, &ha->hw_stats.common.rx_mac_crtl_frames,
                "rx_mac_crtl_frames");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_pause_frames",
                CTLFLAG_RD, &ha->hw_stats.common.rx_pause_frames,
                "rx_pause_frames");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_pfc_frames",
                CTLFLAG_RD, &ha->hw_stats.common.rx_pfc_frames,
                "rx_pfc_frames");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_align_errors",
                CTLFLAG_RD, &ha->hw_stats.common.rx_align_errors,
                "rx_align_errors");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_carrier_errors",
                CTLFLAG_RD, &ha->hw_stats.common.rx_carrier_errors,
                "rx_carrier_errors");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_oversize_packets",
                CTLFLAG_RD, &ha->hw_stats.common.rx_oversize_packets,
                "rx_oversize_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_jabbers",
                CTLFLAG_RD, &ha->hw_stats.common.rx_jabbers,
                "rx_jabbers");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_undersize_packets",
                CTLFLAG_RD, &ha->hw_stats.common.rx_undersize_packets,
                "rx_undersize_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_fragments",
                CTLFLAG_RD, &ha->hw_stats.common.rx_fragments,
                "rx_fragments");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_64_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.common.tx_64_byte_packets,
                "tx_64_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_65_to_127_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.common.tx_65_to_127_byte_packets,
                "tx_65_to_127_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_128_to_255_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.common.tx_128_to_255_byte_packets,
                "tx_128_to_255_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_256_to_511_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.common.tx_256_to_511_byte_packets,
                "tx_256_to_511_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_512_to_1023_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.common.tx_512_to_1023_byte_packets,
                "tx_512_to_1023_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_1024_to_1518_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.common.tx_1024_to_1518_byte_packets,
                "tx_1024_to_1518_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_1519_to_2047_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.bb.tx_1519_to_2047_byte_packets,
                "tx_1519_to_2047_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_2048_to_4095_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.bb.tx_2048_to_4095_byte_packets,
                "tx_2048_to_4095_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_4096_to_9216_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.bb.tx_4096_to_9216_byte_packets,
                "tx_4096_to_9216_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_9217_to_16383_byte_packets",
                CTLFLAG_RD, &ha->hw_stats.bb.tx_9217_to_16383_byte_packets,
                "tx_9217_to_16383_byte_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_pause_frames",
                CTLFLAG_RD, &ha->hw_stats.common.tx_pause_frames,
                "tx_pause_frames");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_pfc_frames",
                CTLFLAG_RD, &ha->hw_stats.common.tx_pfc_frames,
                "tx_pfc_frames");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_lpi_entry_count",
                CTLFLAG_RD, &ha->hw_stats.bb.tx_lpi_entry_count,
                "tx_lpi_entry_count");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_total_collisions",
                CTLFLAG_RD, &ha->hw_stats.bb.tx_total_collisions,
                "tx_total_collisions");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "brb_truncates",
                CTLFLAG_RD, &ha->hw_stats.common.brb_truncates,
                "brb_truncates");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "brb_discards",
                CTLFLAG_RD, &ha->hw_stats.common.brb_discards,
                "brb_discards");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_mac_bytes",
                CTLFLAG_RD, &ha->hw_stats.common.rx_mac_bytes,
                "rx_mac_bytes");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_mac_uc_packets",
                CTLFLAG_RD, &ha->hw_stats.common.rx_mac_uc_packets,
                "rx_mac_uc_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_mac_mc_packets",
                CTLFLAG_RD, &ha->hw_stats.common.rx_mac_mc_packets,
                "rx_mac_mc_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_mac_bc_packets",
                CTLFLAG_RD, &ha->hw_stats.common.rx_mac_bc_packets,
                "rx_mac_bc_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "rx_mac_frames_ok",
                CTLFLAG_RD, &ha->hw_stats.common.rx_mac_frames_ok,
                "rx_mac_frames_ok");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_mac_bytes",
                CTLFLAG_RD, &ha->hw_stats.common.tx_mac_bytes,
                "tx_mac_bytes");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_mac_uc_packets",
                CTLFLAG_RD, &ha->hw_stats.common.tx_mac_uc_packets,
                "tx_mac_uc_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_mac_mc_packets",
                CTLFLAG_RD, &ha->hw_stats.common.tx_mac_mc_packets,
                "tx_mac_mc_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_mac_bc_packets",
                CTLFLAG_RD, &ha->hw_stats.common.tx_mac_bc_packets,
                "tx_mac_bc_packets");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "tx_mac_ctrl_frames",
                CTLFLAG_RD, &ha->hw_stats.common.tx_mac_ctrl_frames,
                "tx_mac_ctrl_frames");
	return;
}