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
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  xrcd_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_bmap_release_id (struct ecore_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ecore_rdma_free_xrcd(void	*rdma_cxt,
			  u16	xrcd_id)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "xrcd_id = %08x\n", xrcd_id);

	/* Returns a previously allocated protection domain for reuse */
	OSAL_SPIN_LOCK(&p_hwfn->p_rdma_info->lock);
	ecore_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->xrcd_map, xrcd_id);
	OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->lock);
}