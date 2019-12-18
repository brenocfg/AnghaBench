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
typedef  size_t u8 ;
struct ecore_qm_info {TYPE_1__* qm_vport_params; } ;
struct ecore_hwfn {struct ecore_qm_info qm_info; } ;
struct TYPE_2__ {int vport_wfq; } ;

/* Variables and functions */
 size_t ecore_init_qm_get_num_vports (struct ecore_hwfn*) ; 

__attribute__((used)) static void ecore_init_qm_vport_params(struct ecore_hwfn *p_hwfn)
{
	struct ecore_qm_info *qm_info = &p_hwfn->qm_info;
	u8 i;

	/* all vports participate in weighted fair queueing */
	for (i = 0; i < ecore_init_qm_get_num_vports(p_hwfn); i++)
		qm_info->qm_vport_params[i].vport_wfq = 1;
}