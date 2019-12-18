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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
t3_meminfo(const uint32_t *regs)
{
	enum {
		SG_EGR_CNTX_BADDR       = 0x58,
		SG_CQ_CONTEXT_BADDR     = 0x6c,
		CIM_SDRAM_BASE_ADDR     = 0x28c,
		CIM_SDRAM_ADDR_SIZE     = 0x290,
		TP_CMM_MM_BASE          = 0x314,
		TP_CMM_TIMER_BASE       = 0x318,
		TP_CMM_MM_RX_FLST_BASE  = 0x460,
		TP_CMM_MM_TX_FLST_BASE  = 0x464,
		TP_CMM_MM_PS_FLST_BASE  = 0x468,
		ULPRX_ISCSI_LLIMIT      = 0x50c,
		ULPRX_ISCSI_ULIMIT      = 0x510,
		ULPRX_TDDP_LLIMIT       = 0x51c,
		ULPRX_TDDP_ULIMIT       = 0x520,
		ULPRX_STAG_LLIMIT       = 0x52c,
		ULPRX_STAG_ULIMIT       = 0x530,
		ULPRX_RQ_LLIMIT         = 0x534,
		ULPRX_RQ_ULIMIT         = 0x538,
		ULPRX_PBL_LLIMIT        = 0x53c,
		ULPRX_PBL_ULIMIT        = 0x540,
	};

	unsigned int egr_cntxt = regs[SG_EGR_CNTX_BADDR / 4],
		     cq_cntxt = regs[SG_CQ_CONTEXT_BADDR / 4],
		     timers = regs[TP_CMM_TIMER_BASE / 4] & 0xfffffff,
		     pstructs = regs[TP_CMM_MM_BASE / 4],
		     pstruct_fl = regs[TP_CMM_MM_PS_FLST_BASE / 4],
		     rx_fl = regs[TP_CMM_MM_RX_FLST_BASE / 4],
		     tx_fl = regs[TP_CMM_MM_TX_FLST_BASE / 4],
		     cim_base = regs[CIM_SDRAM_BASE_ADDR / 4],
		     cim_size = regs[CIM_SDRAM_ADDR_SIZE / 4];
	unsigned int iscsi_ll = regs[ULPRX_ISCSI_LLIMIT / 4],
		     iscsi_ul = regs[ULPRX_ISCSI_ULIMIT / 4],
		     tddp_ll = regs[ULPRX_TDDP_LLIMIT / 4],
		     tddp_ul = regs[ULPRX_TDDP_ULIMIT / 4],
		     stag_ll = regs[ULPRX_STAG_LLIMIT / 4],
		     stag_ul = regs[ULPRX_STAG_ULIMIT / 4],
		     rq_ll = regs[ULPRX_RQ_LLIMIT / 4],
		     rq_ul = regs[ULPRX_RQ_ULIMIT / 4],
		     pbl_ll = regs[ULPRX_PBL_LLIMIT / 4],
		     pbl_ul = regs[ULPRX_PBL_ULIMIT / 4];

	printf("CM memory map:\n");
	printf("  TCB region:      0x%08x - 0x%08x [%u]\n", 0, egr_cntxt - 1,
	       egr_cntxt);
	printf("  Egress contexts: 0x%08x - 0x%08x [%u]\n", egr_cntxt,
	       cq_cntxt - 1, cq_cntxt - egr_cntxt);
	printf("  CQ contexts:     0x%08x - 0x%08x [%u]\n", cq_cntxt,
	       timers - 1, timers - cq_cntxt);
	printf("  Timers:          0x%08x - 0x%08x [%u]\n", timers,
	       pstructs - 1, pstructs - timers);
	printf("  Pstructs:        0x%08x - 0x%08x [%u]\n", pstructs,
	       pstruct_fl - 1, pstruct_fl - pstructs);
	printf("  Pstruct FL:      0x%08x - 0x%08x [%u]\n", pstruct_fl,
	       rx_fl - 1, rx_fl - pstruct_fl);
	printf("  Rx FL:           0x%08x - 0x%08x [%u]\n", rx_fl, tx_fl - 1,
	       tx_fl - rx_fl);
	printf("  Tx FL:           0x%08x - 0x%08x [%u]\n", tx_fl, cim_base - 1,
	       cim_base - tx_fl);
	printf("  uP RAM:          0x%08x - 0x%08x [%u]\n", cim_base,
	       cim_base + cim_size - 1, cim_size);

	printf("\nPMRX memory map:\n");
	printf("  iSCSI region:    0x%08x - 0x%08x [%u]\n", iscsi_ll, iscsi_ul,
	       iscsi_ul - iscsi_ll + 1);
	printf("  TCP DDP region:  0x%08x - 0x%08x [%u]\n", tddp_ll, tddp_ul,
	       tddp_ul - tddp_ll + 1);
	printf("  TPT region:      0x%08x - 0x%08x [%u]\n", stag_ll, stag_ul,
	       stag_ul - stag_ll + 1);
	printf("  RQ region:       0x%08x - 0x%08x [%u]\n", rq_ll, rq_ul,
	       rq_ul - rq_ll + 1);
	printf("  PBL region:      0x%08x - 0x%08x [%u]\n", pbl_ll, pbl_ul,
	       pbl_ul - pbl_ll + 1);
	return 0;
}