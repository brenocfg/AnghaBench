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
struct ecore_queue_cid {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_NOTIMPL ; 
 int ECORE_SUCCESS ; 
 scalar_t__ IS_PF (int /*<<< orphan*/ ) ; 
 int ecore_eth_pf_rx_queue_stop (struct ecore_hwfn*,struct ecore_queue_cid*,int,int) ; 
 int /*<<< orphan*/  ecore_eth_queue_cid_release (struct ecore_hwfn*,struct ecore_queue_cid*) ; 
 int ecore_vf_pf_rxq_stop (struct ecore_hwfn*,struct ecore_queue_cid*,int) ; 

enum _ecore_status_t ecore_eth_rx_queue_stop(struct ecore_hwfn *p_hwfn,
					     void *p_rxq,
					     bool eq_completion_only,
					     bool cqe_completion)
{
	struct ecore_queue_cid *p_cid = (struct ecore_queue_cid *)p_rxq;
	enum _ecore_status_t rc = ECORE_NOTIMPL;

	if (IS_PF(p_hwfn->p_dev))
		rc = ecore_eth_pf_rx_queue_stop(p_hwfn, p_cid,
						eq_completion_only,
						cqe_completion);
	else
		rc = ecore_vf_pf_rxq_stop(p_hwfn, p_cid, cqe_completion);

	if (rc == ECORE_SUCCESS)
		ecore_eth_queue_cid_release(p_hwfn, p_cid);
	return rc;
}