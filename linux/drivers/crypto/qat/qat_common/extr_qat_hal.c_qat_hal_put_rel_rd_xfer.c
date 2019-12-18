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
struct icp_qat_fw_loader_handle {int dummy; } ;
typedef  enum icp_qat_uof_regtype { ____Placeholder_icp_qat_uof_regtype } icp_qat_uof_regtype ;

/* Variables and functions */
 unsigned int CE_INUSE_CONTEXTS ; 
 int /*<<< orphan*/  CTX_ENABLES ; 
 int EINVAL ; 
#define  ICP_DR_RD_REL 131 
#define  ICP_DR_REL 130 
#define  ICP_SR_RD_REL 129 
#define  ICP_SR_REL 128 
 int /*<<< orphan*/  SET_AE_XFER (struct icp_qat_fw_loader_handle*,unsigned char,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned char) ; 
 unsigned int qat_hal_rd_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qat_hal_put_rel_rd_xfer(struct icp_qat_fw_loader_handle *handle,
				   unsigned char ae, unsigned char ctx,
				   enum icp_qat_uof_regtype reg_type,
				   unsigned short reg_num, unsigned int val)
{
	int status = 0;
	unsigned int reg_addr;
	unsigned int ctx_enables;
	unsigned short mask;
	unsigned short dr_offset = 0x10;

	status = ctx_enables = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	if (CE_INUSE_CONTEXTS & ctx_enables) {
		if (ctx & 0x1) {
			pr_err("QAT: bad 4-ctx mode,ctx=0x%x\n", ctx);
			return -EINVAL;
		}
		mask = 0x1f;
		dr_offset = 0x20;
	} else {
		mask = 0x0f;
	}
	if (reg_num & ~mask)
		return -EINVAL;
	reg_addr = reg_num + (ctx << 0x5);
	switch (reg_type) {
	case ICP_SR_RD_REL:
	case ICP_SR_REL:
		SET_AE_XFER(handle, ae, reg_addr, val);
		break;
	case ICP_DR_RD_REL:
	case ICP_DR_REL:
		SET_AE_XFER(handle, ae, (reg_addr + dr_offset), val);
		break;
	default:
		status = -EINVAL;
		break;
	}
	return status;
}