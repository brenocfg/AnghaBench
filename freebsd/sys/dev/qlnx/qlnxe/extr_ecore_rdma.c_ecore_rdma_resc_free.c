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
struct ecore_hwfn {TYPE_1__* p_rdma_info; int /*<<< orphan*/  p_dev; } ;
struct TYPE_2__ {void* dev; void* port; int /*<<< orphan*/  xrc_srq_map; int /*<<< orphan*/  srq_map; int /*<<< orphan*/  tid_map; int /*<<< orphan*/  toggle_bits; int /*<<< orphan*/  cq_map; int /*<<< orphan*/  dpi_map; int /*<<< orphan*/  xrcd_map; int /*<<< orphan*/  pd_map; int /*<<< orphan*/  qp_map; int /*<<< orphan*/  cid_map; } ;

/* Variables and functions */
 scalar_t__ IS_IWARP (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,void*) ; 
 void* OSAL_NULL ; 
 int /*<<< orphan*/  ecore_iwarp_resc_free (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_rdma_bmap_free (struct ecore_hwfn*,int /*<<< orphan*/ *,int) ; 

void ecore_rdma_resc_free(struct ecore_hwfn *p_hwfn)
{
	if (IS_IWARP(p_hwfn))
		ecore_iwarp_resc_free(p_hwfn);

	ecore_rdma_bmap_free(p_hwfn, &p_hwfn->p_rdma_info->cid_map, 1);
	ecore_rdma_bmap_free(p_hwfn, &p_hwfn->p_rdma_info->qp_map, 1);
	ecore_rdma_bmap_free(p_hwfn, &p_hwfn->p_rdma_info->pd_map, 1);
	ecore_rdma_bmap_free(p_hwfn, &p_hwfn->p_rdma_info->xrcd_map, 1);
	ecore_rdma_bmap_free(p_hwfn, &p_hwfn->p_rdma_info->dpi_map, 1);
	ecore_rdma_bmap_free(p_hwfn, &p_hwfn->p_rdma_info->cq_map, 1);
	ecore_rdma_bmap_free(p_hwfn, &p_hwfn->p_rdma_info->toggle_bits, 0);
	ecore_rdma_bmap_free(p_hwfn, &p_hwfn->p_rdma_info->tid_map, 1);
	ecore_rdma_bmap_free(p_hwfn, &p_hwfn->p_rdma_info->srq_map, 1);
	ecore_rdma_bmap_free(p_hwfn, &p_hwfn->p_rdma_info->xrc_srq_map, 1);

	OSAL_FREE(p_hwfn->p_dev, p_hwfn->p_rdma_info->port);
	p_hwfn->p_rdma_info->port = OSAL_NULL;

	OSAL_FREE(p_hwfn->p_dev, p_hwfn->p_rdma_info->dev);
	p_hwfn->p_rdma_info->dev = OSAL_NULL;
}