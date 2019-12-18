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
typedef  unsigned short uint64_t ;
struct icp_qat_fw_loader_handle {int dummy; } ;
typedef  enum icp_qat_uof_regtype { ____Placeholder_icp_qat_uof_regtype } icp_qat_uof_regtype ;

/* Variables and functions */
 unsigned int ACS_ACNO ; 
 int /*<<< orphan*/  ACTIVE_CTX_STATUS ; 
 int /*<<< orphan*/  ALU_OUT ; 
 unsigned short BAD_REGADDR ; 
 int /*<<< orphan*/  CTX_ARB_CNTL ; 
 int /*<<< orphan*/  CTX_ENABLES ; 
 int EINVAL ; 
#define  ICP_GPA_REL 128 
 unsigned int IGNORE_W1C_MASK ; 
 unsigned int UA_ECS ; 
 int /*<<< orphan*/  USTORE_ADDRESS ; 
 int /*<<< orphan*/  USTORE_DATA_LOWER ; 
 int /*<<< orphan*/  USTORE_DATA_UPPER ; 
 int /*<<< orphan*/  pr_err (char*,unsigned short) ; 
 unsigned short qat_hal_get_reg_addr (int,unsigned short) ; 
 int /*<<< orphan*/  qat_hal_get_uwords (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,int,unsigned short*) ; 
 unsigned int qat_hal_rd_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ) ; 
 unsigned short qat_hal_set_uword_ecc (unsigned short) ; 
 int /*<<< orphan*/  qat_hal_wait_cycles (struct icp_qat_fw_loader_handle*,unsigned char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qat_hal_wr_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  qat_hal_wr_uwords (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,int,unsigned short*) ; 

__attribute__((used)) static int qat_hal_rd_rel_reg(struct icp_qat_fw_loader_handle *handle,
			      unsigned char ae, unsigned char ctx,
			      enum icp_qat_uof_regtype reg_type,
			      unsigned short reg_num, unsigned int *data)
{
	unsigned int savctx, uaddr, uwrd_lo, uwrd_hi;
	unsigned int ctxarb_cntl, ustore_addr, ctx_enables;
	unsigned short reg_addr;
	int status = 0;
	uint64_t insts, savuword;

	reg_addr = qat_hal_get_reg_addr(reg_type, reg_num);
	if (reg_addr == BAD_REGADDR) {
		pr_err("QAT: bad regaddr=0x%x\n", reg_addr);
		return -EINVAL;
	}
	switch (reg_type) {
	case ICP_GPA_REL:
		insts = 0xA070000000ull | (reg_addr & 0x3ff);
		break;
	default:
		insts = (uint64_t)0xA030000000ull | ((reg_addr & 0x3ff) << 10);
		break;
	}
	savctx = qat_hal_rd_ae_csr(handle, ae, ACTIVE_CTX_STATUS);
	ctxarb_cntl = qat_hal_rd_ae_csr(handle, ae, CTX_ARB_CNTL);
	ctx_enables = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	ctx_enables &= IGNORE_W1C_MASK;
	if (ctx != (savctx & ACS_ACNO))
		qat_hal_wr_ae_csr(handle, ae, ACTIVE_CTX_STATUS,
				  ctx & ACS_ACNO);
	qat_hal_get_uwords(handle, ae, 0, 1, &savuword);
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx_enables);
	ustore_addr = qat_hal_rd_ae_csr(handle, ae, USTORE_ADDRESS);
	uaddr = UA_ECS;
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, uaddr);
	insts = qat_hal_set_uword_ecc(insts);
	uwrd_lo = (unsigned int)(insts & 0xffffffff);
	uwrd_hi = (unsigned int)(insts >> 0x20);
	qat_hal_wr_ae_csr(handle, ae, USTORE_DATA_LOWER, uwrd_lo);
	qat_hal_wr_ae_csr(handle, ae, USTORE_DATA_UPPER, uwrd_hi);
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, uaddr);
	/* delay for at least 8 cycles */
	qat_hal_wait_cycles(handle, ae, 0x8, 0);
	/*
	 * read ALU output
	 * the instruction should have been executed
	 * prior to clearing the ECS in putUwords
	 */
	*data = qat_hal_rd_ae_csr(handle, ae, ALU_OUT);
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, ustore_addr);
	qat_hal_wr_uwords(handle, ae, 0, 1, &savuword);
	if (ctx != (savctx & ACS_ACNO))
		qat_hal_wr_ae_csr(handle, ae, ACTIVE_CTX_STATUS,
				  savctx & ACS_ACNO);
	qat_hal_wr_ae_csr(handle, ae, CTX_ARB_CNTL, ctxarb_cntl);
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx_enables);

	return status;
}