#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* u32 ;
struct pvr_s {int dummy; } ;
struct device_node {int dummy; } ;
struct cpuinfo {void* use_instr; void* use_mult; void* use_fpu; int use_exc; int icache_line_length; int dcache_line_length; void* dcache_wb; int /*<<< orphan*/  ver_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  AREA_OPTIMISED ; 
 int /*<<< orphan*/  CI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCACHE_ADDR_TAG_BITS ; 
 int /*<<< orphan*/  DCACHE_ALLOW_WR ; 
 int /*<<< orphan*/  DCACHE_BASEADDR ; 
 int /*<<< orphan*/  DCACHE_BYTE_SIZE ; 
 int /*<<< orphan*/  DCACHE_HIGHADDR ; 
 int /*<<< orphan*/  DEBUG_ENABLED ; 
 int /*<<< orphan*/  D_LMB ; 
 int /*<<< orphan*/  D_OPB ; 
 int /*<<< orphan*/  EDGE_IS_POSITIVE ; 
 int /*<<< orphan*/  ENDIAN ; 
 int /*<<< orphan*/  FSL_LINKS ; 
 int /*<<< orphan*/  ICACHE_ADDR_TAG_BITS ; 
 int /*<<< orphan*/  ICACHE_ALLOW_WR ; 
 int /*<<< orphan*/  ICACHE_BASEADDR ; 
 int /*<<< orphan*/  ICACHE_BYTE_SIZE ; 
 int /*<<< orphan*/  ICACHE_HIGHADDR ; 
 int /*<<< orphan*/  INTERRUPT_IS_EDGE ; 
 int /*<<< orphan*/  I_LMB ; 
 int /*<<< orphan*/  I_OPB ; 
 int /*<<< orphan*/  MMU_PRIVINS ; 
 int /*<<< orphan*/  NUMBER_OF_PC_BRK ; 
 int /*<<< orphan*/  NUMBER_OF_RD_ADDR_BRK ; 
 int /*<<< orphan*/  NUMBER_OF_WR_ADDR_BRK ; 
 int PVR_DCACHE_LINE_LEN (struct pvr_s) ; 
 void* PVR_DCACHE_USE_WRITEBACK (struct pvr_s) ; 
 int PVR_DIV_ZERO_EXCEPTION (struct pvr_s) ; 
 int PVR_DOPB_BUS_EXCEPTION (struct pvr_s) ; 
 int PVR_FPU_EXCEPTION (struct pvr_s) ; 
 int PVR_FSL_EXCEPTION (struct pvr_s) ; 
 int PVR_ICACHE_LINE_LEN (struct pvr_s) ; 
 int PVR_ILL_OPCODE_EXCEPTION (struct pvr_s) ; 
 int PVR_IOPB_BUS_EXCEPTION (struct pvr_s) ; 
 int PVR_OPCODE_0x0_ILLEGAL (struct pvr_s) ; 
 int PVR_UNALIGNED_EXCEPTION (struct pvr_s) ; 
 int PVR_USE_BARREL (struct pvr_s) ; 
 int PVR_USE_DIV (struct pvr_s) ; 
 int PVR_USE_FPU (struct pvr_s) ; 
 int PVR_USE_FPU2 (struct pvr_s) ; 
 int PVR_USE_HW_MUL (struct pvr_s) ; 
 int PVR_USE_MSR_INSTR (struct pvr_s) ; 
 int PVR_USE_MUL64 (struct pvr_s) ; 
 int PVR_USE_PCMP_INSTR (struct pvr_s) ; 
 int /*<<< orphan*/  TARGET_FAMILY ; 
 int /*<<< orphan*/  USER1 ; 
 int /*<<< orphan*/  USER2 ; 
 int /*<<< orphan*/  USE_DCACHE ; 
 int /*<<< orphan*/  USE_ICACHE ; 
 int /*<<< orphan*/  USE_MMU ; 
 int /*<<< orphan*/  VERSION ; 
 int /*<<< orphan*/  area_optimised ; 
 int /*<<< orphan*/  dcache_base ; 
 int /*<<< orphan*/  dcache_high ; 
 int /*<<< orphan*/  dcache_size ; 
 int /*<<< orphan*/  dcache_tagbits ; 
 int /*<<< orphan*/  dcache_write ; 
 int /*<<< orphan*/  endian ; 
 int /*<<< orphan*/  err_printk (char*) ; 
 int /*<<< orphan*/  fpga_family_code ; 
 int /*<<< orphan*/  get_pvr (struct pvr_s*) ; 
 int /*<<< orphan*/  hw_debug ; 
 int /*<<< orphan*/  icache_base ; 
 int /*<<< orphan*/  icache_high ; 
 int /*<<< orphan*/  icache_size ; 
 int /*<<< orphan*/  icache_tagbits ; 
 int /*<<< orphan*/  icache_write ; 
 int /*<<< orphan*/  irq_edge ; 
 int /*<<< orphan*/  irq_positive ; 
 int /*<<< orphan*/  mmu ; 
 int /*<<< orphan*/  mmu_privins ; 
 int /*<<< orphan*/  num_fsl ; 
 int /*<<< orphan*/  num_pc_brk ; 
 int /*<<< orphan*/  num_rd_brk ; 
 int /*<<< orphan*/  num_wr_brk ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pvr_user1 ; 
 int /*<<< orphan*/  pvr_user2 ; 
 int /*<<< orphan*/  use_dcache ; 
 int /*<<< orphan*/  use_dlmb ; 
 int /*<<< orphan*/  use_dopb ; 
 int /*<<< orphan*/  use_icache ; 
 int /*<<< orphan*/  use_ilmb ; 
 int /*<<< orphan*/  use_iopb ; 
 int /*<<< orphan*/  ver_code ; 

void set_cpuinfo_pvr_full(struct cpuinfo *ci, struct device_node *cpu)
{
	struct pvr_s pvr;
	u32 temp; /* for saving temp value */
	get_pvr(&pvr);

	CI(ver_code, VERSION);
	if (!ci->ver_code) {
		pr_err("ERROR: MB has broken PVR regs -> use DTS setting\n");
		return;
	}

	temp = PVR_USE_BARREL(pvr) | PVR_USE_MSR_INSTR(pvr) |
		PVR_USE_PCMP_INSTR(pvr) | PVR_USE_DIV(pvr);
	if (ci->use_instr != temp)
		err_printk("BARREL, MSR, PCMP or DIV");
	ci->use_instr = temp;

	temp = PVR_USE_HW_MUL(pvr) | PVR_USE_MUL64(pvr);
	if (ci->use_mult != temp)
		err_printk("HW_MUL");
	ci->use_mult = temp;

	temp = PVR_USE_FPU(pvr) | PVR_USE_FPU2(pvr);
	if (ci->use_fpu != temp)
		err_printk("HW_FPU");
	ci->use_fpu = temp;

	ci->use_exc = PVR_OPCODE_0x0_ILLEGAL(pvr) |
			PVR_UNALIGNED_EXCEPTION(pvr) |
			PVR_ILL_OPCODE_EXCEPTION(pvr) |
			PVR_IOPB_BUS_EXCEPTION(pvr) |
			PVR_DOPB_BUS_EXCEPTION(pvr) |
			PVR_DIV_ZERO_EXCEPTION(pvr) |
			PVR_FPU_EXCEPTION(pvr) |
			PVR_FSL_EXCEPTION(pvr);

	CI(pvr_user1, USER1);
	CI(pvr_user2, USER2);

	CI(mmu, USE_MMU);
	CI(mmu_privins, MMU_PRIVINS);
	CI(endian, ENDIAN);

	CI(use_icache, USE_ICACHE);
	CI(icache_tagbits, ICACHE_ADDR_TAG_BITS);
	CI(icache_write, ICACHE_ALLOW_WR);
	ci->icache_line_length = PVR_ICACHE_LINE_LEN(pvr) << 2;
	CI(icache_size, ICACHE_BYTE_SIZE);
	CI(icache_base, ICACHE_BASEADDR);
	CI(icache_high, ICACHE_HIGHADDR);

	CI(use_dcache, USE_DCACHE);
	CI(dcache_tagbits, DCACHE_ADDR_TAG_BITS);
	CI(dcache_write, DCACHE_ALLOW_WR);
	ci->dcache_line_length = PVR_DCACHE_LINE_LEN(pvr) << 2;
	CI(dcache_size, DCACHE_BYTE_SIZE);
	CI(dcache_base, DCACHE_BASEADDR);
	CI(dcache_high, DCACHE_HIGHADDR);

	temp = PVR_DCACHE_USE_WRITEBACK(pvr);
	if (ci->dcache_wb != temp)
		err_printk("DCACHE WB");
	ci->dcache_wb = temp;

	CI(use_dopb, D_OPB);
	CI(use_iopb, I_OPB);
	CI(use_dlmb, D_LMB);
	CI(use_ilmb, I_LMB);
	CI(num_fsl, FSL_LINKS);

	CI(irq_edge, INTERRUPT_IS_EDGE);
	CI(irq_positive, EDGE_IS_POSITIVE);

	CI(area_optimised, AREA_OPTIMISED);

	CI(hw_debug, DEBUG_ENABLED);
	CI(num_pc_brk, NUMBER_OF_PC_BRK);
	CI(num_rd_brk, NUMBER_OF_RD_ADDR_BRK);
	CI(num_wr_brk, NUMBER_OF_WR_ADDR_BRK);

	CI(fpga_family_code, TARGET_FAMILY);
}