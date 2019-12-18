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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cid_map; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  ECORE_ELEM_CXT ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_bmap_release_id (struct ecore_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ecore_cxt_dynamic_ilt_alloc (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ecore_cxt_get_proto_cid_start (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int ecore_rdma_bmap_alloc_id (struct ecore_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_iwarp_alloc_cid(struct ecore_hwfn *p_hwfn, u32 *cid)
{
	enum _ecore_status_t rc;

	OSAL_SPIN_LOCK(&p_hwfn->p_rdma_info->lock);

	rc = ecore_rdma_bmap_alloc_id(p_hwfn,
				      &p_hwfn->p_rdma_info->cid_map,
				      cid);

	OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->lock);
	*cid += ecore_cxt_get_proto_cid_start(p_hwfn,
					      p_hwfn->p_rdma_info->proto);
	if (rc != ECORE_SUCCESS) {
		DP_NOTICE(p_hwfn, false, "Failed in allocating iwarp cid\n");
		return rc;
	}

	rc = ecore_cxt_dynamic_ilt_alloc(p_hwfn, ECORE_ELEM_CXT, *cid);

	if (rc != ECORE_SUCCESS) {
		OSAL_SPIN_LOCK(&p_hwfn->p_rdma_info->lock);
		*cid -= ecore_cxt_get_proto_cid_start(p_hwfn,
					     p_hwfn->p_rdma_info->proto);

		ecore_bmap_release_id(p_hwfn,
				      &p_hwfn->p_rdma_info->cid_map,
				      *cid);

		OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->lock);
	}

	return rc;
}