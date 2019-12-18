#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  deactivate; int /*<<< orphan*/  activate; int /*<<< orphan*/  queue_active; int /*<<< orphan*/  defrag; int /*<<< orphan*/  wake; int /*<<< orphan*/  stall; int /*<<< orphan*/  pkt_done; int /*<<< orphan*/  done; int /*<<< orphan*/  req; } ;
struct TYPE_11__ {int /*<<< orphan*/  lro_queued; int /*<<< orphan*/  lro_bad_csum; int /*<<< orphan*/  lro_flushed; } ;
struct TYPE_10__ {int /*<<< orphan*/  cnt; } ;
struct TYPE_9__ {int /*<<< orphan*/  cnt; } ;
struct mxge_slice_state {TYPE_4__ tx; TYPE_3__ lc; TYPE_2__ rx_big; TYPE_1__ rx_small; void* sysctl_tree; struct sysctl_ctx_list sysctl_ctx; TYPE_6__* fw_stats; } ;
struct TYPE_13__ {int num_slices; void* slice_sysctl_tree; struct mxge_slice_state* ss; struct sysctl_ctx_list slice_sysctl_ctx; int /*<<< orphan*/  watchdog_resets; int /*<<< orphan*/  read_write_dma; int /*<<< orphan*/  write_dma; int /*<<< orphan*/  read_dma; int /*<<< orphan*/  wc; int /*<<< orphan*/  tx_boundary; int /*<<< orphan*/  link_width; int /*<<< orphan*/  product_code_string; int /*<<< orphan*/  serial_number_string; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  dev; } ;
typedef  TYPE_5__ mxge_softc_t ;
struct TYPE_14__ {TYPE_5__ dropped_unicast_filtered; TYPE_5__ dropped_runt; TYPE_5__ dropped_pause; TYPE_5__ dropped_overrun; TYPE_5__ dropped_no_small_buffer; TYPE_5__ dropped_no_big_buffer; TYPE_5__ dropped_multicast_filtered; TYPE_5__ dropped_link_overflow; TYPE_5__ dropped_link_error_or_filtered; TYPE_5__ dropped_bad_phy; TYPE_5__ dropped_bad_crc32; TYPE_5__ rdma_tags_available; TYPE_5__ link_up; } ;
typedef  TYPE_6__ mcp_irq_data_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 void* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U64 (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (void*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 void* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxge_change_flow_control ; 
 int /*<<< orphan*/  mxge_change_intr_coal ; 
 int /*<<< orphan*/  mxge_change_throttle ; 
 int /*<<< orphan*/  mxge_deassert_wait ; 
 int /*<<< orphan*/  mxge_handle_be32 ; 
 int /*<<< orphan*/  mxge_verbose ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  sysctl_ctx_init (struct sysctl_ctx_list*) ; 

__attribute__((used)) static void
mxge_add_sysctls(mxge_softc_t *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *children;
	mcp_irq_data_t *fw;
	struct mxge_slice_state *ss;
	int slice;
	char slice_num[8];

	ctx = device_get_sysctl_ctx(sc->dev);
	children = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev));
	fw = sc->ss[0].fw_stats;

	/* random information */
	SYSCTL_ADD_STRING(ctx, children, OID_AUTO,
		       "firmware_version",
		       CTLFLAG_RD, sc->fw_version,
		       0, "firmware version");
	SYSCTL_ADD_STRING(ctx, children, OID_AUTO,
		       "serial_number",
		       CTLFLAG_RD, sc->serial_number_string,
		       0, "serial number");
	SYSCTL_ADD_STRING(ctx, children, OID_AUTO,
		       "product_code",
		       CTLFLAG_RD, sc->product_code_string,
		       0, "product_code");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO,
		       "pcie_link_width",
		       CTLFLAG_RD, &sc->link_width,
		       0, "tx_boundary");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO,
		       "tx_boundary",
		       CTLFLAG_RD, &sc->tx_boundary,
		       0, "tx_boundary");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO,
		       "write_combine",
		       CTLFLAG_RD, &sc->wc,
		       0, "write combining PIO?");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO,
		       "read_dma_MBs",
		       CTLFLAG_RD, &sc->read_dma,
		       0, "DMA Read speed in MB/s");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO,
		       "write_dma_MBs",
		       CTLFLAG_RD, &sc->write_dma,
		       0, "DMA Write speed in MB/s");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO,
		       "read_write_dma_MBs",
		       CTLFLAG_RD, &sc->read_write_dma,
		       0, "DMA concurrent Read/Write speed in MB/s");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO,
		       "watchdog_resets",
		       CTLFLAG_RD, &sc->watchdog_resets,
		       0, "Number of times NIC was reset");


	/* performance related tunables */
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"intr_coal_delay",
			CTLTYPE_INT|CTLFLAG_RW, sc,
			0, mxge_change_intr_coal,
			"I", "interrupt coalescing delay in usecs");

	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"throttle",
			CTLTYPE_INT|CTLFLAG_RW, sc,
			0, mxge_change_throttle,
			"I", "transmit throttling");

	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"flow_control_enabled",
			CTLTYPE_INT|CTLFLAG_RW, sc,
			0, mxge_change_flow_control,
			"I", "interrupt coalescing delay in usecs");

	SYSCTL_ADD_INT(ctx, children, OID_AUTO,
		       "deassert_wait",
		       CTLFLAG_RW, &mxge_deassert_wait,
		       0, "Wait for IRQ line to go low in ihandler");

	/* stats block from firmware is in network byte order.
	   Need to swap it */
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"link_up",
			CTLTYPE_INT|CTLFLAG_RD, &fw->link_up,
			0, mxge_handle_be32,
			"I", "link up");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"rdma_tags_available",
			CTLTYPE_INT|CTLFLAG_RD, &fw->rdma_tags_available,
			0, mxge_handle_be32,
			"I", "rdma_tags_available");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"dropped_bad_crc32",
			CTLTYPE_INT|CTLFLAG_RD,
			&fw->dropped_bad_crc32,
			0, mxge_handle_be32,
			"I", "dropped_bad_crc32");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"dropped_bad_phy",
			CTLTYPE_INT|CTLFLAG_RD,
			&fw->dropped_bad_phy,
			0, mxge_handle_be32,
			"I", "dropped_bad_phy");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"dropped_link_error_or_filtered",
			CTLTYPE_INT|CTLFLAG_RD,
			&fw->dropped_link_error_or_filtered,
			0, mxge_handle_be32,
			"I", "dropped_link_error_or_filtered");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"dropped_link_overflow",
			CTLTYPE_INT|CTLFLAG_RD, &fw->dropped_link_overflow,
			0, mxge_handle_be32,
			"I", "dropped_link_overflow");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"dropped_multicast_filtered",
			CTLTYPE_INT|CTLFLAG_RD,
			&fw->dropped_multicast_filtered,
			0, mxge_handle_be32,
			"I", "dropped_multicast_filtered");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"dropped_no_big_buffer",
			CTLTYPE_INT|CTLFLAG_RD, &fw->dropped_no_big_buffer,
			0, mxge_handle_be32,
			"I", "dropped_no_big_buffer");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"dropped_no_small_buffer",
			CTLTYPE_INT|CTLFLAG_RD,
			&fw->dropped_no_small_buffer,
			0, mxge_handle_be32,
			"I", "dropped_no_small_buffer");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"dropped_overrun",
			CTLTYPE_INT|CTLFLAG_RD, &fw->dropped_overrun,
			0, mxge_handle_be32,
			"I", "dropped_overrun");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"dropped_pause",
			CTLTYPE_INT|CTLFLAG_RD,
			&fw->dropped_pause,
			0, mxge_handle_be32,
			"I", "dropped_pause");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"dropped_runt",
			CTLTYPE_INT|CTLFLAG_RD, &fw->dropped_runt,
			0, mxge_handle_be32,
			"I", "dropped_runt");

	SYSCTL_ADD_PROC(ctx, children, OID_AUTO,
			"dropped_unicast_filtered",
			CTLTYPE_INT|CTLFLAG_RD, &fw->dropped_unicast_filtered,
			0, mxge_handle_be32,
			"I", "dropped_unicast_filtered");

	/* verbose printing? */
	SYSCTL_ADD_INT(ctx, children, OID_AUTO,
		       "verbose",
		       CTLFLAG_RW, &mxge_verbose,
		       0, "verbose printing");

	/* add counters exported for debugging from all slices */
	sysctl_ctx_init(&sc->slice_sysctl_ctx);
	sc->slice_sysctl_tree =
		SYSCTL_ADD_NODE(&sc->slice_sysctl_ctx, children, OID_AUTO,
				"slice", CTLFLAG_RD, 0, "");

	for (slice = 0; slice < sc->num_slices; slice++) {
		ss = &sc->ss[slice];
		sysctl_ctx_init(&ss->sysctl_ctx);
		ctx = &ss->sysctl_ctx;
		children = SYSCTL_CHILDREN(sc->slice_sysctl_tree);
		sprintf(slice_num, "%d", slice);
		ss->sysctl_tree =
			SYSCTL_ADD_NODE(ctx, children, OID_AUTO, slice_num,
					CTLFLAG_RD, 0, "");
		children = SYSCTL_CHILDREN(ss->sysctl_tree);
		SYSCTL_ADD_INT(ctx, children, OID_AUTO,
			       "rx_small_cnt",
			       CTLFLAG_RD, &ss->rx_small.cnt,
			       0, "rx_small_cnt");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO,
			       "rx_big_cnt",
			       CTLFLAG_RD, &ss->rx_big.cnt,
			       0, "rx_small_cnt");
		SYSCTL_ADD_U64(ctx, children, OID_AUTO,
			       "lro_flushed", CTLFLAG_RD, &ss->lc.lro_flushed,
			       0, "number of lro merge queues flushed");

		SYSCTL_ADD_U64(ctx, children, OID_AUTO,
			       "lro_bad_csum", CTLFLAG_RD, &ss->lc.lro_bad_csum,
			       0, "number of bad csums preventing LRO");

		SYSCTL_ADD_U64(ctx, children, OID_AUTO,
			       "lro_queued", CTLFLAG_RD, &ss->lc.lro_queued,
			       0, "number of frames appended to lro merge"
			       "queues");

#ifndef IFNET_BUF_RING
		/* only transmit from slice 0 for now */
		if (slice > 0)
			continue;
#endif
		SYSCTL_ADD_INT(ctx, children, OID_AUTO,
			       "tx_req",
			       CTLFLAG_RD, &ss->tx.req,
			       0, "tx_req");

		SYSCTL_ADD_INT(ctx, children, OID_AUTO,
			       "tx_done",
			       CTLFLAG_RD, &ss->tx.done,
			       0, "tx_done");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO,
			       "tx_pkt_done",
			       CTLFLAG_RD, &ss->tx.pkt_done,
			       0, "tx_done");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO,
			       "tx_stall",
			       CTLFLAG_RD, &ss->tx.stall,
			       0, "tx_stall");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO,
			       "tx_wake",
			       CTLFLAG_RD, &ss->tx.wake,
			       0, "tx_wake");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO,
			       "tx_defrag",
			       CTLFLAG_RD, &ss->tx.defrag,
			       0, "tx_defrag");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO,
			       "tx_queue_active",
			       CTLFLAG_RD, &ss->tx.queue_active,
			       0, "tx_queue_active");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO,
			       "tx_activate",
			       CTLFLAG_RD, &ss->tx.activate,
			       0, "tx_activate");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO,
			       "tx_deactivate",
			       CTLFLAG_RD, &ss->tx.deactivate,
			       0, "tx_deactivate");
	}
}