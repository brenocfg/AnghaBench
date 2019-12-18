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
typedef  int uint32_t ;
struct al_hal_eth_adapter {scalar_t__ rev_id; TYPE_2__* ec_regs_base; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_gcp_legacy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_comp_desc; } ;
struct TYPE_5__ {TYPE_1__ gen_v3; TYPE_3__ rfw_v3; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_REV_ID_2 ; 
 int AL_ETH_RX_PROTOCOL_DETECT_ENTRIES_NUM ; 
 int EC_GEN_V3_RX_COMP_DESC_W0_L3_CKS_RES_SEL ; 
 int EC_GEN_V3_RX_COMP_DESC_W3_DEC_STAT_13_L4_CKS_RES_SEL ; 
 int EC_GEN_V3_RX_COMP_DESC_W3_DEC_STAT_14_L3_CKS_RES_SEL ; 
 int EC_GEN_V3_RX_COMP_DESC_W3_DEC_STAT_15_CRC_RES_SEL ; 
 int /*<<< orphan*/  al_assert (int) ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * al_eth_generic_rx_crc_gcp ; 
 int /*<<< orphan*/  al_eth_rx_generic_crc_table_entry_set (struct al_hal_eth_adapter*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int,int) ; 

int al_eth_rx_generic_crc_table_init(struct al_hal_eth_adapter *adapter)
	{
	int idx;
	uint32_t val;

	al_assert((adapter->rev_id > AL_ETH_REV_ID_2));

	al_dbg("eth [%s]: enable rx_generic_crc\n", adapter->name);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_legacy, 0x0);

	for (idx = 0; idx < AL_ETH_RX_PROTOCOL_DETECT_ENTRIES_NUM; idx++)
		al_eth_rx_generic_crc_table_entry_set(adapter, idx,
				&al_eth_generic_rx_crc_gcp[idx]);

	val = EC_GEN_V3_RX_COMP_DESC_W3_DEC_STAT_15_CRC_RES_SEL |
			EC_GEN_V3_RX_COMP_DESC_W3_DEC_STAT_14_L3_CKS_RES_SEL |
			EC_GEN_V3_RX_COMP_DESC_W3_DEC_STAT_13_L4_CKS_RES_SEL |
			EC_GEN_V3_RX_COMP_DESC_W0_L3_CKS_RES_SEL;
	al_reg_write32_masked(&adapter->ec_regs_base->gen_v3.rx_comp_desc,
			val, val);
	return 0;
}