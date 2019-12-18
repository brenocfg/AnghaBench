#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  size_t uint32_t ;
struct TYPE_2__ {scalar_t__ pf_srn; } ;
struct octeon_device {scalar_t__ msix_on; TYPE_1__ sriov_info; struct lio_instr_queue** instr_queue; } ;
struct lio_instr_queue {int base_addr_dma; scalar_t__ reset_instr_cnt; int /*<<< orphan*/  inst_cnt_reg; int /*<<< orphan*/  doorbell_reg; int /*<<< orphan*/  max_count; } ;

/* Variables and functions */
 int LIO_CN23XX_INTR_CINT_ENB ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_IQ_BASE_ADDR64 (size_t) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_IQ_DOORBELL (size_t) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_IQ_INSTR_COUNT64 (size_t) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_IQ_SIZE (size_t) ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lio_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_csr32 (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lio_cn23xx_pf_setup_iq_regs(struct octeon_device *oct, uint32_t iq_no)
{
	struct lio_instr_queue	*iq = oct->instr_queue[iq_no];
	uint64_t		pkt_in_done;

	iq_no += oct->sriov_info.pf_srn;

	/* Write the start of the input queue's ring and its size  */
	lio_write_csr64(oct, LIO_CN23XX_SLI_IQ_BASE_ADDR64(iq_no),
			iq->base_addr_dma);
	lio_write_csr32(oct, LIO_CN23XX_SLI_IQ_SIZE(iq_no), iq->max_count);

	/*
	 * Remember the doorbell & instruction count register addr
	 * for this queue
	 */
	iq->doorbell_reg = LIO_CN23XX_SLI_IQ_DOORBELL(iq_no);
	iq->inst_cnt_reg = LIO_CN23XX_SLI_IQ_INSTR_COUNT64(iq_no);
	lio_dev_dbg(oct, "InstQ[%d]:dbell reg @ 0x%x instcnt_reg @ 0x%x\n",
		    iq_no, iq->doorbell_reg, iq->inst_cnt_reg);

	/*
	 * Store the current instruction counter (used in flush_iq
	 * calculation)
	 */
	pkt_in_done = lio_read_csr64(oct, iq->inst_cnt_reg);

	if (oct->msix_on) {
		/* Set CINT_ENB to enable IQ interrupt   */
		lio_write_csr64(oct, iq->inst_cnt_reg,
				(pkt_in_done | LIO_CN23XX_INTR_CINT_ENB));
	} else {
		/*
		 * Clear the count by writing back what we read, but don't
		 * enable interrupts
		 */
		lio_write_csr64(oct, iq->inst_cnt_reg, pkt_in_done);
	}

	iq->reset_instr_cnt = 0;
}