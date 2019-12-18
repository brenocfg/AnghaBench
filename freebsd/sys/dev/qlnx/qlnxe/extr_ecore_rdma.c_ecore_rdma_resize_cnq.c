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
struct ecore_rdma_resize_cnq_in_params {int /*<<< orphan*/  cnq_id; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_NOTIMPL ; 

enum _ecore_status_t ecore_rdma_resize_cnq(void			      *rdma_cxt,
				struct ecore_rdma_resize_cnq_in_params *params)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "cnq_id = %08x\n", params->cnq_id);

	/* @@@TBD: waiting for fw (there is no ramrod yet) */
	return ECORE_NOTIMPL;
}