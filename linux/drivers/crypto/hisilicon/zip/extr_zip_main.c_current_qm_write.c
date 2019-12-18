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
typedef  int u32 ;
struct hisi_zip_ctrl {int num_vfs; } ;
struct TYPE_2__ {int curr_qm_qp_num; } ;
struct hisi_qm {int qp_num; int ctrl_qp_num; scalar_t__ io_base; TYPE_1__ debug; } ;
struct ctrl_debug_file {struct hisi_zip_ctrl* ctrl; } ;

/* Variables and functions */
 int CURRENT_Q_MASK ; 
 int EINVAL ; 
 scalar_t__ QM_DFX_CQE_CNT_VF_CQN ; 
 scalar_t__ QM_DFX_DB_CNT_VF ; 
 scalar_t__ QM_DFX_MB_CNT_VF ; 
 scalar_t__ QM_DFX_SQE_CNT_VF_SQN ; 
 struct hisi_qm* file_to_qm (struct ctrl_debug_file*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int current_qm_write(struct ctrl_debug_file *file, u32 val)
{
	struct hisi_qm *qm = file_to_qm(file);
	struct hisi_zip_ctrl *ctrl = file->ctrl;
	u32 vfq_num;
	u32 tmp;

	if (val > ctrl->num_vfs)
		return -EINVAL;

	/* Calculate curr_qm_qp_num and store */
	if (val == 0) {
		qm->debug.curr_qm_qp_num = qm->qp_num;
	} else {
		vfq_num = (qm->ctrl_qp_num - qm->qp_num) / ctrl->num_vfs;
		if (val == ctrl->num_vfs)
			qm->debug.curr_qm_qp_num = qm->ctrl_qp_num -
				qm->qp_num - (ctrl->num_vfs - 1) * vfq_num;
		else
			qm->debug.curr_qm_qp_num = vfq_num;
	}

	writel(val, qm->io_base + QM_DFX_MB_CNT_VF);
	writel(val, qm->io_base + QM_DFX_DB_CNT_VF);

	tmp = val |
	      (readl(qm->io_base + QM_DFX_SQE_CNT_VF_SQN) & CURRENT_Q_MASK);
	writel(tmp, qm->io_base + QM_DFX_SQE_CNT_VF_SQN);

	tmp = val |
	      (readl(qm->io_base + QM_DFX_CQE_CNT_VF_CQN) & CURRENT_Q_MASK);
	writel(tmp, qm->io_base + QM_DFX_CQE_CNT_VF_CQN);

	return  0;
}