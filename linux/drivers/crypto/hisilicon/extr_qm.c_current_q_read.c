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
typedef  int u32 ;
struct hisi_qm {scalar_t__ io_base; } ;
struct debugfs_file {int dummy; } ;

/* Variables and functions */
 int QM_DFX_QN_SHIFT ; 
 scalar_t__ QM_DFX_SQE_CNT_VF_SQN ; 
 struct hisi_qm* file_to_qm (struct debugfs_file*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static u32 current_q_read(struct debugfs_file *file)
{
	struct hisi_qm *qm = file_to_qm(file);

	return readl(qm->io_base + QM_DFX_SQE_CNT_VF_SQN) >> QM_DFX_QN_SHIFT;
}