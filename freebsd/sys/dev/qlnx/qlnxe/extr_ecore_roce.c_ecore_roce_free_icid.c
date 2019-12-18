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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct ecore_rdma_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  cid_map; int /*<<< orphan*/  proto; } ;
struct ecore_hwfn {struct ecore_rdma_info* p_rdma_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_bmap_release_id (struct ecore_hwfn*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ecore_cxt_get_proto_cid_start (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_roce_free_icid(struct ecore_hwfn *p_hwfn, u16 icid)
{
	struct ecore_rdma_info *p_rdma_info = p_hwfn->p_rdma_info;
	u32 start_cid, cid;

	start_cid = ecore_cxt_get_proto_cid_start(p_hwfn, p_rdma_info->proto);
	cid = icid - start_cid;

	OSAL_SPIN_LOCK(&p_rdma_info->lock);

	ecore_bmap_release_id(p_hwfn, &p_rdma_info->cid_map, cid);

	OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->lock);
}