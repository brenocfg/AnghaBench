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
struct ecore_rdma_start_in_params {int dummy; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_SUCCESS ; 
 scalar_t__ IS_IWARP (struct ecore_hwfn*) ; 
 int ecore_iwarp_setup (struct ecore_hwfn*,struct ecore_rdma_start_in_params*) ; 
 int /*<<< orphan*/  ecore_rdma_init_devinfo (struct ecore_hwfn*,struct ecore_rdma_start_in_params*) ; 
 int /*<<< orphan*/  ecore_rdma_init_events (struct ecore_hwfn*,struct ecore_rdma_start_in_params*) ; 
 int ecore_rdma_init_hw (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_rdma_init_port (struct ecore_hwfn*) ; 
 int ecore_rdma_reserve_lkey (struct ecore_hwfn*) ; 
 int ecore_rdma_start_fw (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_rdma_start_in_params*) ; 
 int ecore_roce_setup (struct ecore_hwfn*) ; 

__attribute__((used)) static enum _ecore_status_t ecore_rdma_setup(struct ecore_hwfn    *p_hwfn,
				struct ecore_ptt                  *p_ptt,
				struct ecore_rdma_start_in_params *params)
{
	enum _ecore_status_t rc = 0;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "RDMA setup\n");

	ecore_rdma_init_devinfo(p_hwfn, params);
	ecore_rdma_init_port(p_hwfn);
	ecore_rdma_init_events(p_hwfn, params);

	rc = ecore_rdma_reserve_lkey(p_hwfn);
	if (rc != ECORE_SUCCESS)
		return rc;

	rc = ecore_rdma_init_hw(p_hwfn, p_ptt);
	if (rc != ECORE_SUCCESS)
		return rc;

	if (IS_IWARP(p_hwfn)) {
		rc = ecore_iwarp_setup(p_hwfn, params);
		if (rc != ECORE_SUCCESS)
			return rc;
	} else {
		rc = ecore_roce_setup(p_hwfn);
		if (rc != ECORE_SUCCESS)
			return rc;
	}

	return ecore_rdma_start_fw(p_hwfn, p_ptt, params);
}