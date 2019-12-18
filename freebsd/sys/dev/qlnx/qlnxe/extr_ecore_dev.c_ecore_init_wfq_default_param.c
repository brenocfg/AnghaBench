#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_vports; TYPE_1__* qm_vport_params; } ;
struct ecore_hwfn {TYPE_2__ qm_info; } ;
struct TYPE_3__ {int vport_wfq; } ;

/* Variables and functions */

__attribute__((used)) static void ecore_init_wfq_default_param(struct ecore_hwfn *p_hwfn)

{
	int i;

	for (i = 0; i < p_hwfn->qm_info.num_vports; i++)
		p_hwfn->qm_info.qm_vport_params[i].vport_wfq = 1;
}