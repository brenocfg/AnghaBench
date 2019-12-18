#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int* out_mask_pair; int* in_mask_pair; int* reg_out_mask; } ;
struct TYPE_8__ {TYPE_3__ atu; } ;
struct al_pcie_regs {TYPE_2__* port_regs; TYPE_4__ app; } ;
struct al_pcie_port {scalar_t__ rev_id; int /*<<< orphan*/  port_id; struct al_pcie_regs* regs; } ;
struct al_pcie_atu_region {int direction; int index; int base_addr; int target_addr; scalar_t__ match_mode; int limit; scalar_t__ cfg_shift_mode; int tlp_type; int attr; int function_match_bypass_mode_number; int msg_code; int bar_number; int response; scalar_t__ enable_attr_match_mode; scalar_t__ enable_msg_match_mode; scalar_t__ invert_matching; scalar_t__ function_match_bypass_mode; int /*<<< orphan*/  enable; int /*<<< orphan*/  enforce_ob_atu_region_set; } ;
typedef  scalar_t__ limit_sz_msk ;
typedef  enum al_pcie_operating_mode { ____Placeholder_al_pcie_operating_mode } al_pcie_operating_mode ;
struct TYPE_5__ {int /*<<< orphan*/  cr2; int /*<<< orphan*/  cr1; int /*<<< orphan*/  limit_addr; int /*<<< orphan*/  upper_target_addr; int /*<<< orphan*/  lower_target_addr; int /*<<< orphan*/  upper_base_addr; int /*<<< orphan*/  lower_base_addr; int /*<<< orphan*/  index; } ;
struct TYPE_6__ {TYPE_1__ iatu; } ;

/* Variables and functions */
 unsigned int AL_BIT (int) ; 
 int AL_FALSE ; 
 int AL_PCIE_ATU_DIR_OUTBOUND ; 
 int AL_PCIE_OPERATING_MODE_EP ; 
 scalar_t__ AL_PCIE_REV_ID_2 ; 
 scalar_t__ AL_PCIE_REV_ID_3 ; 
 int AL_PCIE_TLP_TYPE_IO ; 
 int AL_PCIE_TLP_TYPE_MEM ; 
 int /*<<< orphan*/  AL_REG_BIT_VAL_SET (int,int,int) ; 
 int /*<<< orphan*/  AL_REG_FIELD_SET (int,int,int,int) ; 
 scalar_t__ AL_TRUE ; 
 int EINVAL ; 
 int PCIE_IATU_CR1_FUNC_NUM_MASK ; 
 int PCIE_IATU_CR1_FUNC_NUM_SHIFT ; 
 int PCIE_IATU_CR2_FUNC_NUM_TRANS_BYPASS_FUNC_MATCH_ENABLE_MASK ; 
 int PCIE_IATU_CR2_FUNC_NUM_TRANS_BYPASS_FUNC_MATCH_ENABLE_SHIFT ; 
 int PCIE_W_ATU_MASK_EVEN_ODD_ATU_MASK_40_32_EVEN_MASK ; 
 unsigned int PCIE_W_ATU_MASK_EVEN_ODD_ATU_MASK_40_32_EVEN_SHIFT ; 
 int PCIE_W_ATU_MASK_EVEN_ODD_ATU_MASK_40_32_ODD_MASK ; 
 unsigned int PCIE_W_ATU_MASK_EVEN_ODD_ATU_MASK_40_32_ODD_SHIFT ; 
 int /*<<< orphan*/  al_assert (int) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ al_pcie_is_link_started (struct al_pcie_port*) ; 
 int al_pcie_operating_mode_get (struct al_pcie_port*) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int*,int,unsigned int) ; 

int
al_pcie_atu_region_set(
	struct al_pcie_port *pcie_port,
	struct al_pcie_atu_region *atu_region)
{
	struct al_pcie_regs *regs = pcie_port->regs;
	enum al_pcie_operating_mode op_mode = al_pcie_operating_mode_get(pcie_port);
	uint32_t reg = 0;

	/**
	 * Addressing RMN: 5384
	 *
	 * RMN description:
	 * From SNPS (also included in the data book) Dynamic iATU Programming
	 * With AHB/AXI Bridge Module When the bridge slave interface clock
	 * (hresetn or slv_aclk) is asynchronous to the PCIe native core clock
	 * (core_clk), you must not update the iATU registers while operations
	 * are in progress on the AHB/AXI bridge slave interface. The iATU
	 * registers are in the core_clk clock domain. The register outputs are
	 * used in the AHB/AXI bridge slave interface clock domain. There is no
	 * synchronization logic between these registers and the AHB/AXI bridge
	 * slave interface.
	 *
	 * Software flow:
	 * Do not allow configuring Outbound iATU after link is started
	 */
	if ((atu_region->direction == AL_PCIE_ATU_DIR_OUTBOUND)
		&& (al_pcie_is_link_started(pcie_port))) {
		if (!atu_region->enforce_ob_atu_region_set) {
			al_err("PCIe %d: setting OB iATU after link is started is not allowed\n",
				pcie_port->port_id);
			al_assert(AL_FALSE);
			return -EINVAL;
		} else {
			al_info("PCIe %d: setting OB iATU even after link is started\n",
				pcie_port->port_id);
		}
	}

	/*TODO : add sanity check */
	AL_REG_FIELD_SET(reg, 0xF, 0, atu_region->index);
	AL_REG_BIT_VAL_SET(reg, 31, atu_region->direction);
	al_reg_write32(&regs->port_regs->iatu.index, reg);

	al_reg_write32(&regs->port_regs->iatu.lower_base_addr,
			(uint32_t)(atu_region->base_addr & 0xFFFFFFFF));
	al_reg_write32(&regs->port_regs->iatu.upper_base_addr,
			(uint32_t)((atu_region->base_addr >> 32)& 0xFFFFFFFF));
	al_reg_write32(&regs->port_regs->iatu.lower_target_addr,
			(uint32_t)(atu_region->target_addr & 0xFFFFFFFF));
	al_reg_write32(&regs->port_regs->iatu.upper_target_addr,
			(uint32_t)((atu_region->target_addr >> 32)& 0xFFFFFFFF));

	/* configure the limit, not needed when working in BAR match mode */
	if (atu_region->match_mode == 0) {
		uint32_t limit_reg_val;
		uint32_t *limit_ext_reg =
			(atu_region->direction == AL_PCIE_ATU_DIR_OUTBOUND) ?
			&regs->app.atu.out_mask_pair[atu_region->index / 2] :
			&regs->app.atu.in_mask_pair[atu_region->index / 2];
		uint32_t limit_ext_reg_mask =
			(atu_region->index % 2) ?
			PCIE_W_ATU_MASK_EVEN_ODD_ATU_MASK_40_32_ODD_MASK :
			PCIE_W_ATU_MASK_EVEN_ODD_ATU_MASK_40_32_EVEN_MASK;
		unsigned int limit_ext_reg_shift =
			(atu_region->index % 2) ?
			PCIE_W_ATU_MASK_EVEN_ODD_ATU_MASK_40_32_ODD_SHIFT :
			PCIE_W_ATU_MASK_EVEN_ODD_ATU_MASK_40_32_EVEN_SHIFT;
		uint64_t limit_sz_msk =
			atu_region->limit - atu_region->base_addr;
		uint32_t limit_ext_reg_val = (uint32_t)(((limit_sz_msk) >>
					32) & 0xFFFFFFFF);

		if (limit_ext_reg_val) {
			limit_reg_val =	(uint32_t)((limit_sz_msk) & 0xFFFFFFFF);
			al_assert(limit_reg_val == 0xFFFFFFFF);
		} else {
			limit_reg_val = (uint32_t)(atu_region->limit &
					0xFFFFFFFF);
		}

		al_reg_write32_masked(
				limit_ext_reg,
				limit_ext_reg_mask,
				limit_ext_reg_val << limit_ext_reg_shift);

		al_reg_write32(&regs->port_regs->iatu.limit_addr,
				limit_reg_val);
	}


	/**
	* Addressing RMN: 3186
	*
	* RMN description:
	* Bug in SNPS IP (versions 4.21 , 4.10a-ea02)
	* In CFG request created via outbound atu (shift mode) bits [27:12] go to
	* [31:16] , the shifting is correct , however the ATU leaves bit [15:12]
	* to their original values, this is then transmited in the tlp .
	* Those bits are currently reserved ,bit might be non-resv. in future generations .
	*
	* Software flow:
	* Enable HW fix
	* rev=REV1,REV2 set bit 15 in corresponding app_reg.atu.out_mask
	* rev>REV2 set corresponding bit is app_reg.atu.reg_out_mask
	*/
	if ((atu_region->cfg_shift_mode == AL_TRUE) &&
		(atu_region->direction == AL_PCIE_ATU_DIR_OUTBOUND)) {
		if (pcie_port->rev_id > AL_PCIE_REV_ID_2) {
			al_reg_write32_masked(regs->app.atu.reg_out_mask,
			1 << (atu_region->index) ,
			1 << (atu_region->index));
		} else {
			uint32_t *limit_ext_reg =
				(atu_region->direction == AL_PCIE_ATU_DIR_OUTBOUND) ?
				&regs->app.atu.out_mask_pair[atu_region->index / 2] :
				&regs->app.atu.in_mask_pair[atu_region->index / 2];
			uint32_t limit_ext_reg_mask =
				(atu_region->index % 2) ?
				PCIE_W_ATU_MASK_EVEN_ODD_ATU_MASK_40_32_ODD_MASK :
				PCIE_W_ATU_MASK_EVEN_ODD_ATU_MASK_40_32_EVEN_MASK;
			unsigned int limit_ext_reg_shift =
				(atu_region->index % 2) ?
				PCIE_W_ATU_MASK_EVEN_ODD_ATU_MASK_40_32_ODD_SHIFT :
				PCIE_W_ATU_MASK_EVEN_ODD_ATU_MASK_40_32_EVEN_SHIFT;

			al_reg_write32_masked(
				limit_ext_reg,
				limit_ext_reg_mask,
				(AL_BIT(15)) << limit_ext_reg_shift);
		}
	}

	reg = 0;
	AL_REG_FIELD_SET(reg, 0x1F, 0, atu_region->tlp_type);
	AL_REG_FIELD_SET(reg, 0x3 << 9, 9, atu_region->attr);


	if ((pcie_port->rev_id == AL_PCIE_REV_ID_3)
		&& (op_mode == AL_PCIE_OPERATING_MODE_EP)
		&& (atu_region->function_match_bypass_mode)) {
		AL_REG_FIELD_SET(reg,
			PCIE_IATU_CR1_FUNC_NUM_MASK,
			PCIE_IATU_CR1_FUNC_NUM_SHIFT,
			atu_region->function_match_bypass_mode_number);
	}

	al_reg_write32(&regs->port_regs->iatu.cr1, reg);

	/* Enable/disable the region. */
	reg = 0;
	AL_REG_FIELD_SET(reg, 0xFF, 0, atu_region->msg_code);
	AL_REG_FIELD_SET(reg, 0x700, 8, atu_region->bar_number);
	AL_REG_FIELD_SET(reg, 0x3 << 24, 24, atu_region->response);
	AL_REG_BIT_VAL_SET(reg, 16, atu_region->enable_attr_match_mode == AL_TRUE);
	AL_REG_BIT_VAL_SET(reg, 21, atu_region->enable_msg_match_mode == AL_TRUE);
	AL_REG_BIT_VAL_SET(reg, 28, atu_region->cfg_shift_mode == AL_TRUE);
	AL_REG_BIT_VAL_SET(reg, 29, atu_region->invert_matching == AL_TRUE);
	if (atu_region->tlp_type == AL_PCIE_TLP_TYPE_MEM || atu_region->tlp_type == AL_PCIE_TLP_TYPE_IO)
		AL_REG_BIT_VAL_SET(reg, 30, !!atu_region->match_mode);
	AL_REG_BIT_VAL_SET(reg, 31, !!atu_region->enable);

	/* In outbound, enable function bypass
	 * In inbound, enable function match mode
	 * Note: this is the same bit, has different meanings in ob/ib ATUs
	 */
	if (op_mode == AL_PCIE_OPERATING_MODE_EP)
		AL_REG_FIELD_SET(reg,
			PCIE_IATU_CR2_FUNC_NUM_TRANS_BYPASS_FUNC_MATCH_ENABLE_MASK,
			PCIE_IATU_CR2_FUNC_NUM_TRANS_BYPASS_FUNC_MATCH_ENABLE_SHIFT,
			atu_region->function_match_bypass_mode ? 0x1 : 0x0);

	al_reg_write32(&regs->port_regs->iatu.cr2, reg);

	return 0;
}