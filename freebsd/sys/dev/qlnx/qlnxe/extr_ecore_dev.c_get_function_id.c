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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int concrete_fid; scalar_t__ opaque_fid; } ;
struct ecore_hwfn {int abs_pf_id; TYPE_1__ hw_info; void* port_id; void* rel_pf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  ECORE_MSG_PROBE ; 
 void* GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PXP_CONCRETE_FID_PFID ; 
 int /*<<< orphan*/  PXP_CONCRETE_FID_PORT ; 
 int /*<<< orphan*/  PXP_PF_ME_CONCRETE_ADDR ; 
 int /*<<< orphan*/  PXP_PF_ME_OPAQUE_ADDR ; 
 int REG_RD (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_function_id(struct ecore_hwfn *p_hwfn)
{
	/* ME Register */
	p_hwfn->hw_info.opaque_fid = (u16) REG_RD(p_hwfn,
						  PXP_PF_ME_OPAQUE_ADDR);

	p_hwfn->hw_info.concrete_fid = REG_RD(p_hwfn, PXP_PF_ME_CONCRETE_ADDR);

	/* Bits 16-19 from the ME registers are the pf_num */
	p_hwfn->abs_pf_id = (p_hwfn->hw_info.concrete_fid >> 16) & 0xf;
	p_hwfn->rel_pf_id = GET_FIELD(p_hwfn->hw_info.concrete_fid,
				      PXP_CONCRETE_FID_PFID);
	p_hwfn->port_id = GET_FIELD(p_hwfn->hw_info.concrete_fid,
				    PXP_CONCRETE_FID_PORT);

	DP_VERBOSE(p_hwfn, ECORE_MSG_PROBE,
		   "Read ME register: Concrete 0x%08x Opaque 0x%04x\n",
		   p_hwfn->hw_info.concrete_fid, p_hwfn->hw_info.opaque_fid);
}