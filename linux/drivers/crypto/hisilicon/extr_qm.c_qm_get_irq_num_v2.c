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
typedef  int /*<<< orphan*/  u32 ;
struct hisi_qm {scalar_t__ fun_type; } ;

/* Variables and functions */
 scalar_t__ QM_HW_PF ; 
 int /*<<< orphan*/  QM_IRQ_NUM_PF_V2 ; 
 int /*<<< orphan*/  QM_IRQ_NUM_VF_V2 ; 

__attribute__((used)) static u32 qm_get_irq_num_v2(struct hisi_qm *qm)
{
	if (qm->fun_type == QM_HW_PF)
		return QM_IRQ_NUM_PF_V2;
	else
		return QM_IRQ_NUM_VF_V2;
}