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
typedef  scalar_t__ u16 ;
struct ecore_vf_info {int num_sbs; scalar_t__* igu_sbs; int /*<<< orphan*/  abs_vf_id; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 

__attribute__((used)) static bool ecore_iov_validate_sb(struct ecore_hwfn *p_hwfn,
				  struct ecore_vf_info *p_vf,
				  u16 sb_idx)
{
	int i;

	for (i = 0; i < p_vf->num_sbs; i++)
		if (p_vf->igu_sbs[i] == sb_idx)
			return true;

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
		   "VF[0%02x] - tried using sb_idx %04x which doesn't exist as one of its 0x%02x SBs\n",
		   p_vf->abs_vf_id, sb_idx, p_vf->num_sbs);

	return false;
}