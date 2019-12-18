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
typedef  int /*<<< orphan*/  u16 ;
struct ecore_vf_info {int num_sbs; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/ * igu_sbs; scalar_t__ concrete_fid; } ;
struct ecore_ptt {int dummy; } ;
struct TYPE_2__ {scalar_t__ concrete_fid; } ;
struct ecore_hwfn {TYPE_1__ hw_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGU_REG_STATISTIC_NUM_VF_MSG_SENT ; 
 int /*<<< orphan*/  ecore_fid_pretend (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_int_igu_init_pure_rt_single (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_iov_vf_igu_reset(struct ecore_hwfn *p_hwfn,
				   struct ecore_ptt *p_ptt,
				   struct ecore_vf_info *vf)
{
	int i;

	/* Set VF masks and configuration - pretend */
	ecore_fid_pretend(p_hwfn, p_ptt, (u16)vf->concrete_fid);

	ecore_wr(p_hwfn, p_ptt, IGU_REG_STATISTIC_NUM_VF_MSG_SENT, 0);

	/* unpretend */
	ecore_fid_pretend(p_hwfn, p_ptt, (u16)p_hwfn->hw_info.concrete_fid);

	/* iterate over all queues, clear sb consumer */
	for (i = 0; i < vf->num_sbs; i++)
		ecore_int_igu_init_pure_rt_single(p_hwfn, p_ptt,
						  vf->igu_sbs[i],
						  vf->opaque_fid, true);
}