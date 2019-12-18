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

__attribute__((used)) static void ecore_iov_unlock_vf_pf_channel(struct ecore_hwfn *p_hwfn,
					   struct ecore_vf_info *vf,
					   u16 expected_tlv)
{
	/*WARN(expected_tlv != vf->op_current,
	     "lock mismatch: expected %s found %s",
	     channel_tlvs_string[expected_tlv],
	     channel_tlvs_string[vf->op_current]);
	     @@@TBD MichalK
	*/

	/* lock the channel */
	/* mutex_unlock(&vf->op_mutex); @@@TBD MichalK add the lock */

	/* log the unlock */
	if (ecore_iov_tlv_supported(expected_tlv))
		DP_VERBOSE(p_hwfn,
			   ECORE_MSG_IOV,
			   "VF[%d]: vf pf channel unlocked by %s\n",
			   vf->abs_vf_id,
			   ecore_channel_tlvs_string[expected_tlv]);
	else
		DP_VERBOSE(p_hwfn,
			   ECORE_MSG_IOV,
			   "VF[%d]: vf pf channel unlocked by %04x\n",
			   vf->abs_vf_id, expected_tlv);

	/* record the locking op */
	/* vf->op_current = CHANNEL_TLV_NONE;*/
}