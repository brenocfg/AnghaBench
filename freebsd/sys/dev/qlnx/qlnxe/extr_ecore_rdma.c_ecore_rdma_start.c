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
struct ecore_rdma_start_in_params {int desired_cnq; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_TIMEOUT ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_rdma_activate (struct ecore_hwfn*) ; 
 int ecore_rdma_alloc (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_rdma_free (struct ecore_hwfn*) ; 
 int ecore_rdma_setup (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_rdma_start_in_params*) ; 

enum _ecore_status_t ecore_rdma_start(void *rdma_cxt,
				struct ecore_rdma_start_in_params *params)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;
	struct ecore_ptt *p_ptt;
	enum _ecore_status_t rc = ECORE_TIMEOUT;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
		   "desired_cnq = %08x\n", params->desired_cnq);

	p_ptt = ecore_ptt_acquire(p_hwfn);
	if (!p_ptt)
		goto err;

	rc = ecore_rdma_alloc(p_hwfn);
	if (rc)
		goto err1;

	rc = ecore_rdma_setup(p_hwfn, p_ptt, params);
	if (rc)
		goto err2;

	ecore_ptt_release(p_hwfn, p_ptt);

	ecore_rdma_activate(p_hwfn);
	return rc;

err2:
	ecore_rdma_free(p_hwfn);
err1:
	ecore_ptt_release(p_hwfn, p_ptt);
err:
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "RDMA start - error, rc = %d\n", rc);
	return rc;
}