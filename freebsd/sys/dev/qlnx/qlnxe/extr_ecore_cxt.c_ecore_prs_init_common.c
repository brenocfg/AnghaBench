#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ is_target; } ;
struct TYPE_6__ {TYPE_2__ fcoe_pf_params; } ;
struct TYPE_4__ {scalar_t__ personality; } ;
struct ecore_hwfn {TYPE_3__ pf_params; TYPE_1__ hw_info; } ;

/* Variables and functions */
 scalar_t__ ECORE_PCI_FCOE ; 
 int /*<<< orphan*/  PRS_REG_SEARCH_RESP_INITIATOR_TYPE_RT_OFFSET ; 
 int /*<<< orphan*/  STORE_RT_REG (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_prs_init_common(struct ecore_hwfn *p_hwfn)
{
	if ((p_hwfn->hw_info.personality == ECORE_PCI_FCOE) &&
	    p_hwfn->pf_params.fcoe_pf_params.is_target)
		STORE_RT_REG(p_hwfn, PRS_REG_SEARCH_RESP_INITIATOR_TYPE_RT_OFFSET, 0);
}