#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  max_count; } ;
struct TYPE_3__ {TYPE_2__ tcp_cid_map; int /*<<< orphan*/  proto; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_IWARP_INVALID_TCP_CID ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ ecore_cxt_get_proto_cid_start (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int ecore_rdma_bmap_alloc_id (struct ecore_hwfn*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_iwarp_alloc_tcp_cid(struct ecore_hwfn *p_hwfn, u32 *cid)
{
	enum _ecore_status_t rc;

	OSAL_SPIN_LOCK(&p_hwfn->p_rdma_info->lock);

	rc = ecore_rdma_bmap_alloc_id(p_hwfn,
				      &p_hwfn->p_rdma_info->tcp_cid_map,
				      cid);

	OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->lock);

	*cid += ecore_cxt_get_proto_cid_start(p_hwfn,
					      p_hwfn->p_rdma_info->proto);
	if (rc != ECORE_SUCCESS) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "can't allocate iwarp tcp cid max-count=%d\n",
			   p_hwfn->p_rdma_info->tcp_cid_map.max_count);

		*cid = ECORE_IWARP_INVALID_TCP_CID;
	}

	return rc;
}