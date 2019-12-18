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
typedef  int u8 ;
typedef  unsigned long long u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct ecore_vf_info {int abs_vf_id; int relative_vf_id; int /*<<< orphan*/  state; } ;
struct ecore_hwfn {TYPE_3__* pf_iov_info; TYPE_2__* p_dev; } ;
struct TYPE_6__ {unsigned long long* pending_flr; } ;
struct TYPE_5__ {TYPE_1__* p_iov_info; } ;
struct TYPE_4__ {int total_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int VF_MAX_STATIC ; 
 int /*<<< orphan*/  VF_RESET ; 
 struct ecore_vf_info* ecore_iov_get_vf_info (struct ecore_hwfn*,int,int) ; 

bool ecore_iov_mark_vf_flr(struct ecore_hwfn *p_hwfn,
			  u32 *p_disabled_vfs)
{
	bool found = false;
	u16 i;

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV, "Marking FLR-ed VFs\n");
	for (i = 0; i < (VF_MAX_STATIC / 32); i++)
		DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
			   "[%08x,...,%08x]: %08x\n",
			   i * 32, (i + 1) * 32 - 1, p_disabled_vfs[i]);

	if (!p_hwfn->p_dev->p_iov_info) {
		DP_NOTICE(p_hwfn, true, "VF flr but no IOV\n");
		return false;
	}

	/* Mark VFs */
	for (i = 0; i < p_hwfn->p_dev->p_iov_info->total_vfs; i++) {
		struct ecore_vf_info *p_vf;
		u8 vfid;

		p_vf = ecore_iov_get_vf_info(p_hwfn, i, false);
		if (!p_vf)
			continue;

		vfid = p_vf->abs_vf_id;
		if ((1 << (vfid % 32)) & p_disabled_vfs[vfid / 32]) {
			u64 *p_flr =  p_hwfn->pf_iov_info->pending_flr;
			u16 rel_vf_id = p_vf->relative_vf_id;

			DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
				   "VF[%d] [rel %d] got FLR-ed\n",
				   vfid, rel_vf_id);

			p_vf->state = VF_RESET;

			/* No need to lock here, since pending_flr should
			 * only change here and before ACKing MFw. Since
			 * MFW will not trigger an additional attention for
			 * VF flr until ACKs, we're safe.
			 */
			p_flr[rel_vf_id / 64] |= 1ULL << (rel_vf_id % 64);
			found = true;
		}
	}

	return found;
}