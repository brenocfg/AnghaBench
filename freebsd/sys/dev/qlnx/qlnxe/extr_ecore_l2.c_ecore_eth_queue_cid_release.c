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
struct ecore_queue_cid {int vf_legacy; scalar_t__ vfid; int /*<<< orphan*/  cid; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int ECORE_QCID_LEGACY_VF_CID ; 
 scalar_t__ ECORE_QUEUE_CID_PF ; 
 scalar_t__ IS_PF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_VFREE (int /*<<< orphan*/ ,struct ecore_queue_cid*) ; 
 int /*<<< orphan*/  _ecore_cxt_release_cid (struct ecore_hwfn*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ecore_eth_queue_qid_usage_del (struct ecore_hwfn*,struct ecore_queue_cid*) ; 

void ecore_eth_queue_cid_release(struct ecore_hwfn *p_hwfn,
				 struct ecore_queue_cid *p_cid)
{
	bool b_legacy_vf = !!(p_cid->vf_legacy &
			      ECORE_QCID_LEGACY_VF_CID);

	/* VFs' CIDs are 0-based in PF-view, and uninitialized on VF.
	 * For legacy vf-queues, the CID doesn't go through here.
	 */
	if (IS_PF(p_hwfn->p_dev) && !b_legacy_vf)
		_ecore_cxt_release_cid(p_hwfn, p_cid->cid, p_cid->vfid);

	/* VFs maintain the index inside queue-zone on their own */
	if (p_cid->vfid == ECORE_QUEUE_CID_PF)
		ecore_eth_queue_qid_usage_del(p_hwfn, p_cid);

	OSAL_VFREE(p_hwfn->p_dev, p_cid);
}