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
struct ecore_spq_entry {int dummy; } ;
struct ecore_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct TYPE_2__ {int /*<<< orphan*/  opaque_fid; } ;
struct ecore_hwfn {TYPE_1__ hw_info; int /*<<< orphan*/  p_dev; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int /*<<< orphan*/  ECORE_ROCE_ICID_TO_QP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_EBLOCK ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_ROCE ; 
 int /*<<< orphan*/  ROCE_RAMROD_DESTROY_UD_QP ; 
 int /*<<< orphan*/  ecore_roce_free_qp (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_sp_init_data*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,int /*<<< orphan*/ ) ; 

enum _ecore_status_t ecore_roce_destroy_ud_qp(void *rdma_cxt, u16 cid)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;
	struct ecore_sp_init_data init_data;
	struct ecore_spq_entry *p_ent;
	enum _ecore_status_t rc;

	if (!rdma_cxt) {
		DP_ERR(p_hwfn->p_dev,
		       "destroy ud qp failed due to NULL rdma_cxt\n");
		return ECORE_INVAL;
	}

	/* Get SPQ entry */
	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.cid = cid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = ECORE_SPQ_MODE_EBLOCK;
	rc = ecore_sp_init_request(p_hwfn, &p_ent, ROCE_RAMROD_DESTROY_UD_QP,
				   PROTOCOLID_ROCE, &init_data);
	if (rc != ECORE_SUCCESS)
		goto err;

	rc = ecore_spq_post(p_hwfn, p_ent, OSAL_NULL);
	if (rc != ECORE_SUCCESS)
		goto err;

	ecore_roce_free_qp(p_hwfn, ECORE_ROCE_ICID_TO_QP(cid));

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "freed a ud qp with cid=%d\n", cid);

	return ECORE_SUCCESS;

err:
	DP_ERR(p_hwfn, "failed destroying a ud qp with cid=%d\n", cid);

	return rc;
}