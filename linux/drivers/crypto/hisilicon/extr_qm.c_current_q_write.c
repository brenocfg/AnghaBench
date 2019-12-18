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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ curr_qm_qp_num; } ;
struct hisi_qm {scalar_t__ io_base; TYPE_1__ debug; } ;
struct debugfs_file {int dummy; } ;

/* Variables and functions */
 scalar_t__ CURRENT_FUN_MASK ; 
 int EINVAL ; 
 scalar_t__ QM_DFX_CQE_CNT_VF_CQN ; 
 scalar_t__ QM_DFX_QN_SHIFT ; 
 scalar_t__ QM_DFX_SQE_CNT_VF_SQN ; 
 struct hisi_qm* file_to_qm (struct debugfs_file*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int current_q_write(struct debugfs_file *file, u32 val)
{
	struct hisi_qm *qm = file_to_qm(file);
	u32 tmp;

	if (val >= qm->debug.curr_qm_qp_num)
		return -EINVAL;

	tmp = val << QM_DFX_QN_SHIFT |
	      (readl(qm->io_base + QM_DFX_SQE_CNT_VF_SQN) & CURRENT_FUN_MASK);
	writel(tmp, qm->io_base + QM_DFX_SQE_CNT_VF_SQN);

	tmp = val << QM_DFX_QN_SHIFT |
	      (readl(qm->io_base + QM_DFX_CQE_CNT_VF_CQN) & CURRENT_FUN_MASK);
	writel(tmp, qm->io_base + QM_DFX_CQE_CNT_VF_CQN);

	return 0;
}