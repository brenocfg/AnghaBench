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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; } ;
struct al_eth_rx_gpd_cam_entry {int rx_gpd_cam_ctrl; scalar_t__ l4_dst_port_lsb_mask; scalar_t__ l3_priority_mask; scalar_t__ outer_l3_len_mask; scalar_t__ parse_ctrl_mask; scalar_t__ inner_l4_proto_idx_mask; scalar_t__ inner_l3_proto_idx_mask; scalar_t__ outer_l4_proto_idx_mask; scalar_t__ outer_l3_proto_idx_mask; scalar_t__ l4_dst_port_lsb; scalar_t__ l3_priority; scalar_t__ outer_l3_len; scalar_t__ parse_ctrl; scalar_t__ inner_l4_proto_idx; scalar_t__ inner_l3_proto_idx; scalar_t__ outer_l4_proto_idx; scalar_t__ outer_l3_proto_idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_gpd_cam_data_1; int /*<<< orphan*/  rx_gpd_cam_data_2; int /*<<< orphan*/  rx_gpd_cam_mask_1; int /*<<< orphan*/  rx_gpd_cam_mask_2; int /*<<< orphan*/  rx_gpd_cam_ctrl; int /*<<< orphan*/  rx_gpd_cam_addr; } ;
struct TYPE_4__ {TYPE_1__ rfw_v3; } ;

/* Variables and functions */
 int AL_ETH_RX_GPD_CAM_CTRL_VALID_SHIFT ; 
 int AL_ETH_RX_GPD_CAM_DATA_2_SHIFT ; 
 int AL_ETH_RX_GPD_CAM_MASK_2_SHIFT ; 
 int AL_ETH_RX_GPD_INNER_L3_PROTO_MASK ; 
 int AL_ETH_RX_GPD_INNER_L3_PROTO_SHIFT ; 
 int AL_ETH_RX_GPD_INNER_L4_PROTO_MASK ; 
 int AL_ETH_RX_GPD_INNER_L4_PROTO_SHIFT ; 
 int AL_ETH_RX_GPD_INNER_PARSE_CTRL_MASK ; 
 int AL_ETH_RX_GPD_INNER_PARSE_CTRL_SHIFT ; 
 int AL_ETH_RX_GPD_L3_PRIORITY_MASK ; 
 int AL_ETH_RX_GPD_L3_PRIORITY_SHIFT ; 
 int AL_ETH_RX_GPD_L4_DST_PORT_LSB_MASK ; 
 int AL_ETH_RX_GPD_L4_DST_PORT_LSB_SHIFT ; 
 int AL_ETH_RX_GPD_OUTER_L3_PROTO_MASK ; 
 int AL_ETH_RX_GPD_OUTER_L3_PROTO_SHIFT ; 
 int AL_ETH_RX_GPD_OUTER_L4_PROTO_MASK ; 
 int AL_ETH_RX_GPD_OUTER_L4_PROTO_SHIFT ; 
 int AL_ETH_RX_GPD_OUTER_PARSE_CTRL_MASK ; 
 int AL_ETH_RX_GPD_OUTER_PARSE_CTRL_SHIFT ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int al_eth_rx_protocol_detect_table_entry_set(struct al_hal_eth_adapter *adapter, uint32_t idx,
		struct al_eth_rx_gpd_cam_entry *rx_gpd_entry)
{
	uint64_t gpd_data;
	uint64_t gpd_mask;

	gpd_data  = ((uint64_t)rx_gpd_entry->outer_l3_proto_idx & AL_ETH_RX_GPD_OUTER_L3_PROTO_MASK) <<
		AL_ETH_RX_GPD_OUTER_L3_PROTO_SHIFT;
	gpd_data |= ((uint64_t)rx_gpd_entry->outer_l4_proto_idx & AL_ETH_RX_GPD_OUTER_L4_PROTO_MASK) <<
		AL_ETH_RX_GPD_OUTER_L4_PROTO_SHIFT;
	gpd_data |= ((uint64_t)rx_gpd_entry->inner_l3_proto_idx & AL_ETH_RX_GPD_INNER_L3_PROTO_MASK) <<
		AL_ETH_RX_GPD_INNER_L3_PROTO_SHIFT;
	gpd_data |= ((uint64_t)rx_gpd_entry->inner_l4_proto_idx & AL_ETH_RX_GPD_INNER_L4_PROTO_MASK) <<
		AL_ETH_RX_GPD_INNER_L4_PROTO_SHIFT;
	gpd_data |= ((uint64_t)rx_gpd_entry->parse_ctrl & AL_ETH_RX_GPD_OUTER_PARSE_CTRL_MASK) <<
		AL_ETH_RX_GPD_OUTER_PARSE_CTRL_SHIFT;
	gpd_data |= ((uint64_t)rx_gpd_entry->outer_l3_len & AL_ETH_RX_GPD_INNER_PARSE_CTRL_MASK) <<
		AL_ETH_RX_GPD_INNER_PARSE_CTRL_SHIFT;
	gpd_data |= ((uint64_t)rx_gpd_entry->l3_priority & AL_ETH_RX_GPD_L3_PRIORITY_MASK) <<
		AL_ETH_RX_GPD_L3_PRIORITY_SHIFT;
	gpd_data |= ((uint64_t)rx_gpd_entry->l4_dst_port_lsb & AL_ETH_RX_GPD_L4_DST_PORT_LSB_MASK) <<
		AL_ETH_RX_GPD_L4_DST_PORT_LSB_SHIFT;

	gpd_mask  = ((uint64_t)rx_gpd_entry->outer_l3_proto_idx_mask & AL_ETH_RX_GPD_OUTER_L3_PROTO_MASK) <<
		AL_ETH_RX_GPD_OUTER_L3_PROTO_SHIFT;
	gpd_mask |= ((uint64_t)rx_gpd_entry->outer_l4_proto_idx_mask & AL_ETH_RX_GPD_OUTER_L4_PROTO_MASK) <<
		AL_ETH_RX_GPD_OUTER_L4_PROTO_SHIFT;
	gpd_mask |= ((uint64_t)rx_gpd_entry->inner_l3_proto_idx_mask & AL_ETH_RX_GPD_INNER_L3_PROTO_MASK) <<
		AL_ETH_RX_GPD_INNER_L3_PROTO_SHIFT;
	gpd_mask |= ((uint64_t)rx_gpd_entry->inner_l4_proto_idx_mask & AL_ETH_RX_GPD_INNER_L4_PROTO_MASK) <<
		AL_ETH_RX_GPD_INNER_L4_PROTO_SHIFT;
	gpd_mask |= ((uint64_t)rx_gpd_entry->parse_ctrl_mask & AL_ETH_RX_GPD_OUTER_PARSE_CTRL_MASK) <<
		AL_ETH_RX_GPD_OUTER_PARSE_CTRL_SHIFT;
	gpd_mask |= ((uint64_t)rx_gpd_entry->outer_l3_len_mask & AL_ETH_RX_GPD_INNER_PARSE_CTRL_MASK) <<
		AL_ETH_RX_GPD_INNER_PARSE_CTRL_SHIFT;
	gpd_mask |= ((uint64_t)rx_gpd_entry->l3_priority_mask & AL_ETH_RX_GPD_L3_PRIORITY_MASK) <<
		AL_ETH_RX_GPD_L3_PRIORITY_SHIFT;
	gpd_mask |= ((uint64_t)rx_gpd_entry->l4_dst_port_lsb_mask & AL_ETH_RX_GPD_L4_DST_PORT_LSB_MASK) <<
		AL_ETH_RX_GPD_L4_DST_PORT_LSB_SHIFT;

	/* Rx Generic protocol detect Cam compare table */
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gpd_cam_addr, idx);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gpd_cam_ctrl,
			(uint32_t)((rx_gpd_entry->rx_gpd_cam_ctrl) << AL_ETH_RX_GPD_CAM_CTRL_VALID_SHIFT));
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gpd_cam_mask_2,
			(uint32_t)(gpd_mask >> AL_ETH_RX_GPD_CAM_MASK_2_SHIFT));
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gpd_cam_mask_1,
			(uint32_t)(gpd_mask));
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gpd_cam_data_2,
			(uint32_t)(gpd_data >> AL_ETH_RX_GPD_CAM_DATA_2_SHIFT));
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gpd_cam_data_1,
			(uint32_t)(gpd_data));
	return 0;
}