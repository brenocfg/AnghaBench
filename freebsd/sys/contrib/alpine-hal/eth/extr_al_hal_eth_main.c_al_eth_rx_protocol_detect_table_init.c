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
struct al_hal_eth_adapter {scalar_t__ rev_id; TYPE_2__* ec_regs_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  gpd_p8; int /*<<< orphan*/  gpd_p7; int /*<<< orphan*/  gpd_p6; int /*<<< orphan*/  gpd_p5; int /*<<< orphan*/  gpd_p4; int /*<<< orphan*/  gpd_p3; int /*<<< orphan*/  gpd_p2; int /*<<< orphan*/  gpd_p1; } ;
struct TYPE_4__ {TYPE_1__ rfw_v3; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_REV_ID_2 ; 
 int /*<<< orphan*/  AL_ETH_RX_GPD_PARSE_RESULT_INNER_L3_PROTO_IDX_OFFSET ; 
 int /*<<< orphan*/  AL_ETH_RX_GPD_PARSE_RESULT_INNER_L4_PROTO_IDX_OFFSET ; 
 int /*<<< orphan*/  AL_ETH_RX_GPD_PARSE_RESULT_INNER_PARSE_CTRL ; 
 int /*<<< orphan*/  AL_ETH_RX_GPD_PARSE_RESULT_L3_PRIORITY ; 
 int /*<<< orphan*/  AL_ETH_RX_GPD_PARSE_RESULT_OUTER_L3_PROTO_IDX_OFFSET ; 
 int /*<<< orphan*/  AL_ETH_RX_GPD_PARSE_RESULT_OUTER_L4_DST_PORT_LSB ; 
 int /*<<< orphan*/  AL_ETH_RX_GPD_PARSE_RESULT_OUTER_L4_PROTO_IDX_OFFSET ; 
 int /*<<< orphan*/  AL_ETH_RX_GPD_PARSE_RESULT_OUTER_PARSE_CTRL ; 
 int AL_ETH_RX_PROTOCOL_DETECT_ENTRIES_NUM ; 
 int /*<<< orphan*/  al_assert (int) ; 
 int /*<<< orphan*/ * al_eth_generic_rx_crc_gpd ; 
 int /*<<< orphan*/  al_eth_rx_protocol_detect_table_entry_set (struct al_hal_eth_adapter*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int al_eth_rx_protocol_detect_table_init(struct al_hal_eth_adapter *adapter)
{
	int idx;
	al_assert((adapter->rev_id > AL_ETH_REV_ID_2));
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.gpd_p1,
			AL_ETH_RX_GPD_PARSE_RESULT_OUTER_L3_PROTO_IDX_OFFSET);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.gpd_p2,
			AL_ETH_RX_GPD_PARSE_RESULT_OUTER_L4_PROTO_IDX_OFFSET);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.gpd_p3,
			AL_ETH_RX_GPD_PARSE_RESULT_INNER_L3_PROTO_IDX_OFFSET);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.gpd_p4,
			AL_ETH_RX_GPD_PARSE_RESULT_INNER_L4_PROTO_IDX_OFFSET);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.gpd_p5,
			AL_ETH_RX_GPD_PARSE_RESULT_OUTER_PARSE_CTRL);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.gpd_p6,
			AL_ETH_RX_GPD_PARSE_RESULT_INNER_PARSE_CTRL);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.gpd_p7,
			AL_ETH_RX_GPD_PARSE_RESULT_L3_PRIORITY);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.gpd_p8,
			AL_ETH_RX_GPD_PARSE_RESULT_OUTER_L4_DST_PORT_LSB);

	for (idx = 0; idx < AL_ETH_RX_PROTOCOL_DETECT_ENTRIES_NUM; idx++)
		al_eth_rx_protocol_detect_table_entry_set(adapter, idx,
				&al_eth_generic_rx_crc_gpd[idx]);
	return 0;
}