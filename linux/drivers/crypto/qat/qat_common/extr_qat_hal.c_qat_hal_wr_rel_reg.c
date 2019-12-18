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
typedef  int uint64_t ;
struct icp_qat_fw_loader_handle {int dummy; } ;
typedef  enum icp_qat_uof_regtype { ____Placeholder_icp_qat_uof_regtype } icp_qat_uof_regtype ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 unsigned short BAD_REGADDR ; 
 int EINVAL ; 
#define  ICP_GPA_REL 128 
 int ICP_NO_DEST ; 
 int /*<<< orphan*/  pr_err (char*,unsigned short) ; 
 int qat_hal_exec_micro_inst (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,int*,int const,int const,int const,int /*<<< orphan*/ *) ; 
 unsigned short qat_hal_get_reg_addr (int,unsigned short) ; 

__attribute__((used)) static int qat_hal_wr_rel_reg(struct icp_qat_fw_loader_handle *handle,
			      unsigned char ae, unsigned char ctx,
			      enum icp_qat_uof_regtype reg_type,
			      unsigned short reg_num, unsigned int data)
{
	unsigned short src_hiaddr, src_lowaddr, dest_addr, data16hi, data16lo;
	uint64_t insts[] = {
		0x0F440000000ull,
		0x0F040000000ull,
		0x0F0000C0300ull,
		0x0E000010000ull
	};
	const int num_inst = ARRAY_SIZE(insts), code_off = 1;
	const int imm_w1 = 0, imm_w0 = 1;

	dest_addr = qat_hal_get_reg_addr(reg_type, reg_num);
	if (dest_addr == BAD_REGADDR) {
		pr_err("QAT: bad destAddr=0x%x\n", dest_addr);
		return -EINVAL;
	}

	data16lo = 0xffff & data;
	data16hi = 0xffff & (data >> 0x10);
	src_hiaddr = qat_hal_get_reg_addr(ICP_NO_DEST, (unsigned short)
					  (0xff & data16hi));
	src_lowaddr = qat_hal_get_reg_addr(ICP_NO_DEST, (unsigned short)
					   (0xff & data16lo));
	switch (reg_type) {
	case ICP_GPA_REL:
		insts[imm_w1] = insts[imm_w1] | ((data16hi >> 8) << 20) |
		    ((src_hiaddr & 0x3ff) << 10) | (dest_addr & 0x3ff);
		insts[imm_w0] = insts[imm_w0] | ((data16lo >> 8) << 20) |
		    ((src_lowaddr & 0x3ff) << 10) | (dest_addr & 0x3ff);
		break;
	default:
		insts[imm_w1] = insts[imm_w1] | ((data16hi >> 8) << 20) |
		    ((dest_addr & 0x3ff) << 10) | (src_hiaddr & 0x3ff);

		insts[imm_w0] = insts[imm_w0] | ((data16lo >> 8) << 20) |
		    ((dest_addr & 0x3ff) << 10) | (src_lowaddr & 0x3ff);
		break;
	}

	return qat_hal_exec_micro_inst(handle, ae, ctx, insts, num_inst,
				       code_off, num_inst * 0x5, NULL);
}