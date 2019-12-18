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
typedef  enum al_eth_rx_desc_lro_context_val_res { ____Placeholder_al_eth_rx_desc_lro_context_val_res } al_eth_rx_desc_lro_context_val_res ;
typedef  enum al_eth_rx_desc_l4_proto_idx_sel { ____Placeholder_al_eth_rx_desc_l4_proto_idx_sel } al_eth_rx_desc_l4_proto_idx_sel ;
typedef  enum al_eth_rx_desc_l4_offset_sel { ____Placeholder_al_eth_rx_desc_l4_offset_sel } al_eth_rx_desc_l4_offset_sel ;
typedef  enum al_eth_rx_desc_l4_chk_res_sel { ____Placeholder_al_eth_rx_desc_l4_chk_res_sel } al_eth_rx_desc_l4_chk_res_sel ;
typedef  enum al_eth_rx_desc_l3_proto_idx_sel { ____Placeholder_al_eth_rx_desc_l3_proto_idx_sel } al_eth_rx_desc_l3_proto_idx_sel ;
typedef  enum al_eth_rx_desc_l3_offset_sel { ____Placeholder_al_eth_rx_desc_l3_offset_sel } al_eth_rx_desc_l3_offset_sel ;
typedef  enum al_eth_rx_desc_l3_chk_res_sel { ____Placeholder_al_eth_rx_desc_l3_chk_res_sel } al_eth_rx_desc_l3_chk_res_sel ;
typedef  enum al_eth_rx_desc_frag_sel { ____Placeholder_al_eth_rx_desc_frag_sel } al_eth_rx_desc_frag_sel ;
struct TYPE_3__ {int /*<<< orphan*/  meta; int /*<<< orphan*/  cfg_a_0; } ;
struct TYPE_4__ {TYPE_1__ rfw; } ;

/* Variables and functions */
 int AL_ETH_FRAG_INNER ; 
 int AL_ETH_L3_OFFSET_INNER ; 
 int AL_ETH_L3_PROTO_IDX_INNER ; 
 int AL_ETH_L4_INNER_OUTER_CHK ; 
 int AL_ETH_L4_OFFSET ; 
 int AL_ETH_L4_OFFSET_INNER ; 
 int AL_ETH_L4_PROTO_IDX_INNER ; 
 int EC_RFW_CFG_A_0_LRO_CONTEXT_SEL ; 
 int EC_RFW_CFG_A_0_META_L3_CHK_RES_SEL_SHIFT ; 
 int EC_RFW_CFG_A_0_META_L4_CHK_RES_SEL ; 
 int EC_RFW_META_FRAG_SEL ; 
 int EC_RFW_META_L3_OFFSET_SEL ; 
 int EC_RFW_META_L3_PROT_SEL ; 
 int EC_RFW_META_L4_OFFSET_SEL ; 
 int EC_RFW_META_L4_PROT_SEL ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

void al_eth_rx_desc_config(
			struct al_hal_eth_adapter *adapter,
			enum al_eth_rx_desc_lro_context_val_res lro_sel,
			enum al_eth_rx_desc_l4_offset_sel l4_offset_sel,
			enum al_eth_rx_desc_l3_offset_sel l3_offset_sel,
			enum al_eth_rx_desc_l4_chk_res_sel l4_sel,
			enum al_eth_rx_desc_l3_chk_res_sel l3_sel,
			enum al_eth_rx_desc_l3_proto_idx_sel l3_proto_sel,
			enum al_eth_rx_desc_l4_proto_idx_sel l4_proto_sel,
			enum al_eth_rx_desc_frag_sel frag_sel)
{
	uint32_t reg_val = 0;

	reg_val |= (lro_sel == AL_ETH_L4_OFFSET) ?
			EC_RFW_CFG_A_0_LRO_CONTEXT_SEL : 0;

	reg_val |= (l4_sel == AL_ETH_L4_INNER_OUTER_CHK) ?
			EC_RFW_CFG_A_0_META_L4_CHK_RES_SEL : 0;

	reg_val |= l3_sel << EC_RFW_CFG_A_0_META_L3_CHK_RES_SEL_SHIFT;

	al_reg_write32(&adapter->ec_regs_base->rfw.cfg_a_0, reg_val);

	reg_val = al_reg_read32(&adapter->ec_regs_base->rfw.meta);
	if (l3_proto_sel == AL_ETH_L3_PROTO_IDX_INNER)
		reg_val |= EC_RFW_META_L3_PROT_SEL;
	else
		reg_val &= ~EC_RFW_META_L3_PROT_SEL;

	if (l4_proto_sel == AL_ETH_L4_PROTO_IDX_INNER)
		reg_val |= EC_RFW_META_L4_PROT_SEL;
	else
		reg_val &= ~EC_RFW_META_L4_PROT_SEL;

	if (l4_offset_sel == AL_ETH_L4_OFFSET_INNER)
		reg_val |= EC_RFW_META_L4_OFFSET_SEL;
	else
		reg_val &= ~EC_RFW_META_L4_OFFSET_SEL;

	if (l3_offset_sel == AL_ETH_L3_OFFSET_INNER)
		reg_val |= EC_RFW_META_L3_OFFSET_SEL;
	else
		reg_val &= ~EC_RFW_META_L3_OFFSET_SEL;

	if (frag_sel == AL_ETH_FRAG_INNER)
		reg_val |= EC_RFW_META_FRAG_SEL;
	else
		reg_val &= ~EC_RFW_META_FRAG_SEL;


	al_reg_write32(&adapter->ec_regs_base->rfw.meta, reg_val);
}