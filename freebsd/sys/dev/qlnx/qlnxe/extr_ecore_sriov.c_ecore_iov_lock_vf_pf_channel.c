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
typedef  size_t u16 ;
struct ecore_vf_info {int /*<<< orphan*/  abs_vf_id; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 size_t* ecore_channel_tlvs_string ; 
 scalar_t__ ecore_iov_tlv_supported (size_t) ; 

__attribute__((used)) static void ecore_iov_lock_vf_pf_channel(struct ecore_hwfn *p_hwfn,
					 struct ecore_vf_info *vf,
					 u16 tlv)
{
	/* lock the channel */
	/* mutex_lock(&vf->op_mutex); @@@TBD MichalK - add lock... */

	/* record the locking op */
	/* vf->op_current = tlv; @@@TBD MichalK */

	/* log the lock */
	if (ecore_iov_tlv_supported(tlv))
		DP_VERBOSE(p_hwfn,
			   ECORE_MSG_IOV,
			   "VF[%d]: vf pf channel locked by %s\n",
			   vf->abs_vf_id,
			   ecore_channel_tlvs_string[tlv]);
	else
		DP_VERBOSE(p_hwfn,
			   ECORE_MSG_IOV,
			   "VF[%d]: vf pf channel locked by %04x\n",
			   vf->abs_vf_id, tlv);
}