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
typedef  int uint32_t ;
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; } ;
struct al_eth_rx_gcp_table_entry {int poly_sel; int crc32_bit_comp; int crc32_bit_swap; int crc32_byte_swap; int data_bit_swap; int data_byte_swap; int trail_size; int head_size; int head_calc; int mask_polarity; int rx_alu_opcode_1; int rx_alu_opcode_2; int rx_alu_opcode_3; int rx_alu_opsel_1; int rx_alu_opsel_2; int rx_alu_opsel_3; int rx_alu_opsel_4; int* gcp_mask; int crc_init; int gcp_table_res; int alu_val; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_gcp_table_alu_val; int /*<<< orphan*/  rx_gcp_table_alu_opsel; int /*<<< orphan*/  rx_gcp_table_alu_opcode; int /*<<< orphan*/  rx_gcp_table_res; int /*<<< orphan*/  rx_gcp_table_crc_init; int /*<<< orphan*/  rx_gcp_table_mask_6; int /*<<< orphan*/  rx_gcp_table_mask_5; int /*<<< orphan*/  rx_gcp_table_mask_4; int /*<<< orphan*/  rx_gcp_table_mask_3; int /*<<< orphan*/  rx_gcp_table_mask_2; int /*<<< orphan*/  rx_gcp_table_mask_1; int /*<<< orphan*/  rx_gcp_table_gen; int /*<<< orphan*/  rx_gcp_table_addr; } ;
struct TYPE_4__ {TYPE_1__ rfw_v3; } ;

/* Variables and functions */
 int AL_ETH_RX_GCP_CRC32_BIT_COMP_MASK ; 
 int AL_ETH_RX_GCP_CRC32_BIT_COMP_SHIFT ; 
 int AL_ETH_RX_GCP_CRC32_BIT_SWAP_MASK ; 
 int AL_ETH_RX_GCP_CRC32_BIT_SWAP_SHIFT ; 
 int AL_ETH_RX_GCP_CRC32_BYTE_SWAP_MASK ; 
 int AL_ETH_RX_GCP_CRC32_BYTE_SWAP_SHIFT ; 
 int AL_ETH_RX_GCP_DATA_BIT_SWAP_MASK ; 
 int AL_ETH_RX_GCP_DATA_BIT_SWAP_SHIFT ; 
 int AL_ETH_RX_GCP_DATA_BYTE_SWAP_MASK ; 
 int AL_ETH_RX_GCP_DATA_BYTE_SWAP_SHIFT ; 
 int AL_ETH_RX_GCP_HEAD_CALC_MASK ; 
 int AL_ETH_RX_GCP_HEAD_CALC_SHIFT ; 
 int AL_ETH_RX_GCP_HEAD_SIZE_MASK ; 
 int AL_ETH_RX_GCP_HEAD_SIZE_SHIFT ; 
 int AL_ETH_RX_GCP_MASK_POLARITY_MASK ; 
 int AL_ETH_RX_GCP_MASK_POLARITY_SHIFT ; 
 int AL_ETH_RX_GCP_OPCODE_1_MASK ; 
 int AL_ETH_RX_GCP_OPCODE_1_SHIFT ; 
 int AL_ETH_RX_GCP_OPCODE_2_MASK ; 
 int AL_ETH_RX_GCP_OPCODE_2_SHIFT ; 
 int AL_ETH_RX_GCP_OPCODE_3_MASK ; 
 int AL_ETH_RX_GCP_OPCODE_3_SHIFT ; 
 int AL_ETH_RX_GCP_OPSEL_1_MASK ; 
 int AL_ETH_RX_GCP_OPSEL_1_SHIFT ; 
 int AL_ETH_RX_GCP_OPSEL_2_MASK ; 
 int AL_ETH_RX_GCP_OPSEL_2_SHIFT ; 
 int AL_ETH_RX_GCP_OPSEL_3_MASK ; 
 int AL_ETH_RX_GCP_OPSEL_3_SHIFT ; 
 int AL_ETH_RX_GCP_OPSEL_4_MASK ; 
 int AL_ETH_RX_GCP_OPSEL_4_SHIFT ; 
 int AL_ETH_RX_GCP_POLY_SEL_MASK ; 
 int AL_ETH_RX_GCP_POLY_SEL_SHIFT ; 
 int AL_ETH_RX_GCP_TRAIL_SIZE_MASK ; 
 int AL_ETH_RX_GCP_TRAIL_SIZE_SHIFT ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_eth_rx_generic_crc_table_entry_set(struct al_hal_eth_adapter *adapter, uint32_t idx,
		struct al_eth_rx_gcp_table_entry *rx_gcp_entry)
{
	uint32_t gcp_table_gen;
	uint32_t rx_alu_opcode;
	uint32_t rx_alu_opsel;

	gcp_table_gen  = (rx_gcp_entry->poly_sel & AL_ETH_RX_GCP_POLY_SEL_MASK) <<
		AL_ETH_RX_GCP_POLY_SEL_SHIFT;
	gcp_table_gen |= (rx_gcp_entry->crc32_bit_comp & AL_ETH_RX_GCP_CRC32_BIT_COMP_MASK) <<
		AL_ETH_RX_GCP_CRC32_BIT_COMP_SHIFT;
	gcp_table_gen |= (rx_gcp_entry->crc32_bit_swap & AL_ETH_RX_GCP_CRC32_BIT_SWAP_MASK) <<
		AL_ETH_RX_GCP_CRC32_BIT_SWAP_SHIFT;
	gcp_table_gen |= (rx_gcp_entry->crc32_byte_swap & AL_ETH_RX_GCP_CRC32_BYTE_SWAP_MASK) <<
		AL_ETH_RX_GCP_CRC32_BYTE_SWAP_SHIFT;
	gcp_table_gen |= (rx_gcp_entry->data_bit_swap & AL_ETH_RX_GCP_DATA_BIT_SWAP_MASK) <<
		AL_ETH_RX_GCP_DATA_BIT_SWAP_SHIFT;
	gcp_table_gen |= (rx_gcp_entry->data_byte_swap & AL_ETH_RX_GCP_DATA_BYTE_SWAP_MASK) <<
		AL_ETH_RX_GCP_DATA_BYTE_SWAP_SHIFT;
	gcp_table_gen |= (rx_gcp_entry->trail_size & AL_ETH_RX_GCP_TRAIL_SIZE_MASK) <<
		AL_ETH_RX_GCP_TRAIL_SIZE_SHIFT;
	gcp_table_gen |= (rx_gcp_entry->head_size & AL_ETH_RX_GCP_HEAD_SIZE_MASK) <<
		AL_ETH_RX_GCP_HEAD_SIZE_SHIFT;
	gcp_table_gen |= (rx_gcp_entry->head_calc & AL_ETH_RX_GCP_HEAD_CALC_MASK) <<
		AL_ETH_RX_GCP_HEAD_CALC_SHIFT;
	gcp_table_gen |= (rx_gcp_entry->mask_polarity & AL_ETH_RX_GCP_MASK_POLARITY_MASK) <<
		AL_ETH_RX_GCP_MASK_POLARITY_SHIFT;

	rx_alu_opcode  = (rx_gcp_entry->rx_alu_opcode_1 & AL_ETH_RX_GCP_OPCODE_1_MASK) <<
		AL_ETH_RX_GCP_OPCODE_1_SHIFT;
	rx_alu_opcode |= (rx_gcp_entry->rx_alu_opcode_2 & AL_ETH_RX_GCP_OPCODE_2_MASK) <<
		AL_ETH_RX_GCP_OPCODE_2_SHIFT;
	rx_alu_opcode |= (rx_gcp_entry->rx_alu_opcode_3 & AL_ETH_RX_GCP_OPCODE_3_MASK) <<
		AL_ETH_RX_GCP_OPCODE_3_SHIFT;
	rx_alu_opsel  = (rx_gcp_entry->rx_alu_opsel_1 & AL_ETH_RX_GCP_OPSEL_1_MASK) <<
		AL_ETH_RX_GCP_OPSEL_1_SHIFT;
	rx_alu_opsel |= (rx_gcp_entry->rx_alu_opsel_2 & AL_ETH_RX_GCP_OPSEL_2_MASK) <<
		AL_ETH_RX_GCP_OPSEL_2_SHIFT;
	rx_alu_opsel |= (rx_gcp_entry->rx_alu_opsel_3 & AL_ETH_RX_GCP_OPSEL_3_MASK) <<
		AL_ETH_RX_GCP_OPSEL_3_SHIFT;
	rx_alu_opsel |= (rx_gcp_entry->rx_alu_opsel_4 & AL_ETH_RX_GCP_OPSEL_4_MASK) <<
		AL_ETH_RX_GCP_OPSEL_4_SHIFT;

	/*  Rx Generic crc prameters table general */
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_addr, idx);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_gen,
			gcp_table_gen);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_mask_1,
			rx_gcp_entry->gcp_mask[0]);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_mask_2,
			rx_gcp_entry->gcp_mask[1]);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_mask_3,
			rx_gcp_entry->gcp_mask[2]);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_mask_4,
			rx_gcp_entry->gcp_mask[3]);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_mask_5,
			rx_gcp_entry->gcp_mask[4]);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_mask_6,
			rx_gcp_entry->gcp_mask[5]);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_crc_init,
			rx_gcp_entry->crc_init);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_res,
			rx_gcp_entry->gcp_table_res);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_alu_opcode,
			rx_alu_opcode);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_alu_opsel,
			rx_alu_opsel);
	al_reg_write32(&adapter->ec_regs_base->rfw_v3.rx_gcp_table_alu_val,
			rx_gcp_entry->alu_val);
	return 0;
}