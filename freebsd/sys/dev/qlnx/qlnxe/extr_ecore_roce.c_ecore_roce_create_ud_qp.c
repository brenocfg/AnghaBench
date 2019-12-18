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
typedef  int u16 ;
struct ecore_spq_entry {int dummy; } ;
struct ecore_sp_init_data {int cid; int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; } ;
struct ecore_rdma_create_qp_out_params {int icid; int qp_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  opaque_fid; } ;
struct ecore_hwfn {TYPE_1__ hw_info; int /*<<< orphan*/  p_dev; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (int /*<<< orphan*/ ,char*,void*,struct ecore_rdma_create_qp_out_params*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_ROCE_QP_TO_ICID (int) ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_EBLOCK ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_ROCE ; 
 int /*<<< orphan*/  ROCE_RAMROD_CREATE_UD_QP ; 
 int ecore_roce_alloc_qp_idx (struct ecore_hwfn*,int*) ; 
 int /*<<< orphan*/  ecore_roce_free_qp (struct ecore_hwfn*,int) ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_sp_init_data*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,int /*<<< orphan*/ ) ; 

enum _ecore_status_t ecore_roce_create_ud_qp(void		*rdma_cxt,
			struct ecore_rdma_create_qp_out_params	*out_params)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;
	struct ecore_sp_init_data init_data;
	struct ecore_spq_entry *p_ent;
	enum _ecore_status_t rc;
	u16 icid, qp_idx;

	if (!rdma_cxt || !out_params) {
		DP_ERR(p_hwfn->p_dev,
		       "ecore roce create ud qp failed due to NULL entry (rdma_cxt=%p, out=%p)\n",
		       rdma_cxt, out_params);
		return ECORE_INVAL;
	}

	rc = ecore_roce_alloc_qp_idx(p_hwfn, &qp_idx);
	if (rc != ECORE_SUCCESS)
		goto err;

	icid = ECORE_ROCE_QP_TO_ICID(qp_idx);

	/* Get SPQ entry */
	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.cid = icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = ECORE_SPQ_MODE_EBLOCK;
	rc = ecore_sp_init_request(p_hwfn, &p_ent, ROCE_RAMROD_CREATE_UD_QP,
				   PROTOCOLID_ROCE, &init_data);
	if (rc != ECORE_SUCCESS)
		goto err1;

	rc = ecore_spq_post(p_hwfn, p_ent, OSAL_NULL);
	if (rc != ECORE_SUCCESS)
		goto err1;

	out_params->icid = icid;
	out_params->qp_id = ((0xFF << 16) | icid);

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "created a ud qp with icid=%d\n",
		   icid);

	return ECORE_SUCCESS;

err1:
	ecore_roce_free_qp(p_hwfn, qp_idx);

err:
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "failed creating a ud qp\n");

	return rc;
}