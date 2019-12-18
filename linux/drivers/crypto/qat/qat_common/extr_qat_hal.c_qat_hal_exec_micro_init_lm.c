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
typedef  int /*<<< orphan*/  uint64_t ;
struct icp_qat_fw_loader_handle {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  ICP_GPA_REL ; 
 int /*<<< orphan*/  ICP_GPB_REL ; 
 int qat_hal_exec_micro_inst (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,int /*<<< orphan*/ *,unsigned int,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qat_hal_rd_rel_reg (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  qat_hal_wr_rel_reg (struct icp_qat_fw_loader_handle*,unsigned char,unsigned char,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int qat_hal_exec_micro_init_lm(struct icp_qat_fw_loader_handle *handle,
				      unsigned char ae, unsigned char ctx,
				      int *pfirst_exec, uint64_t *micro_inst,
				      unsigned int inst_num)
{
	int stat = 0;
	unsigned int gpra0 = 0, gpra1 = 0, gpra2 = 0;
	unsigned int gprb0 = 0, gprb1 = 0;

	if (*pfirst_exec) {
		qat_hal_rd_rel_reg(handle, ae, ctx, ICP_GPA_REL, 0, &gpra0);
		qat_hal_rd_rel_reg(handle, ae, ctx, ICP_GPA_REL, 0x1, &gpra1);
		qat_hal_rd_rel_reg(handle, ae, ctx, ICP_GPA_REL, 0x2, &gpra2);
		qat_hal_rd_rel_reg(handle, ae, ctx, ICP_GPB_REL, 0, &gprb0);
		qat_hal_rd_rel_reg(handle, ae, ctx, ICP_GPB_REL, 0x1, &gprb1);
		*pfirst_exec = 0;
	}
	stat = qat_hal_exec_micro_inst(handle, ae, ctx, micro_inst, inst_num, 1,
				       inst_num * 0x5, NULL);
	if (stat != 0)
		return -EFAULT;
	qat_hal_wr_rel_reg(handle, ae, ctx, ICP_GPA_REL, 0, gpra0);
	qat_hal_wr_rel_reg(handle, ae, ctx, ICP_GPA_REL, 0x1, gpra1);
	qat_hal_wr_rel_reg(handle, ae, ctx, ICP_GPA_REL, 0x2, gpra2);
	qat_hal_wr_rel_reg(handle, ae, ctx, ICP_GPB_REL, 0, gprb0);
	qat_hal_wr_rel_reg(handle, ae, ctx, ICP_GPB_REL, 0x1, gprb1);

	return 0;
}