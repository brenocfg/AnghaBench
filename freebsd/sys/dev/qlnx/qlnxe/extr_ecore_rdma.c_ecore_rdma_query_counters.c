#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ecore_rdma_counters_out_params {unsigned int max_pd; unsigned int max_dpi; unsigned int max_cq; unsigned int max_qp; unsigned int max_tid; unsigned int max_srq; unsigned int max_xrc_srq; unsigned int max_xrcd; void* xrcd_count; void* xrc_srq_count; void* srq_count; void* tid_count; void* qp_count; void* cq_count; void* dpi_count; void* pd_count; } ;
struct ecore_hwfn {TYPE_9__* p_rdma_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_17__ {unsigned long* bitmap; unsigned int max_count; } ;
struct TYPE_16__ {unsigned long* bitmap; unsigned int max_count; } ;
struct TYPE_15__ {unsigned long* bitmap; unsigned int max_count; } ;
struct TYPE_14__ {unsigned long* bitmap; unsigned int max_count; } ;
struct TYPE_13__ {unsigned long* bitmap; unsigned int max_count; } ;
struct TYPE_12__ {unsigned long* bitmap; unsigned int max_count; } ;
struct TYPE_11__ {unsigned long* bitmap; unsigned int max_count; } ;
struct TYPE_10__ {unsigned long* bitmap; unsigned int max_count; } ;
struct TYPE_18__ {TYPE_8__ xrcd_map; TYPE_7__ xrc_srq_map; TYPE_6__ srq_map; TYPE_5__ tid_map; TYPE_4__ qp_map; TYPE_3__ cq_map; TYPE_2__ dpi_map; TYPE_1__ pd_map; } ;

/* Variables and functions */
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 void* OSAL_BITMAP_WEIGHT (unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_rdma_counters_out_params*,int /*<<< orphan*/ ,int) ; 

enum _ecore_status_t
ecore_rdma_query_counters(void *rdma_cxt,
			  struct ecore_rdma_counters_out_params *out_params)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;
	unsigned long *bitmap;
	unsigned int nbits;

	if (!p_hwfn->p_rdma_info)
		return ECORE_INVAL;

	OSAL_MEMSET(out_params, 0, sizeof(*out_params));

	bitmap = p_hwfn->p_rdma_info->pd_map.bitmap;
	nbits = p_hwfn->p_rdma_info->pd_map.max_count;
	out_params->pd_count = OSAL_BITMAP_WEIGHT(bitmap, nbits);
	out_params->max_pd = nbits;

	bitmap = p_hwfn->p_rdma_info->dpi_map.bitmap;
	nbits = p_hwfn->p_rdma_info->dpi_map.max_count;
	out_params->dpi_count = OSAL_BITMAP_WEIGHT(bitmap, nbits);
	out_params->max_dpi = nbits;

	bitmap = p_hwfn->p_rdma_info->cq_map.bitmap;
	nbits = p_hwfn->p_rdma_info->cq_map.max_count;
	out_params->cq_count = OSAL_BITMAP_WEIGHT(bitmap, nbits);
	out_params->max_cq = nbits;

	bitmap = p_hwfn->p_rdma_info->qp_map.bitmap;
	nbits = p_hwfn->p_rdma_info->qp_map.max_count;
	out_params->qp_count = OSAL_BITMAP_WEIGHT(bitmap, nbits);
	out_params->max_qp = nbits;

	bitmap = p_hwfn->p_rdma_info->tid_map.bitmap;
	nbits = p_hwfn->p_rdma_info->tid_map.max_count;
	out_params->tid_count = OSAL_BITMAP_WEIGHT(bitmap, nbits);
	out_params->max_tid = nbits;

	bitmap = p_hwfn->p_rdma_info->srq_map.bitmap;
	nbits = p_hwfn->p_rdma_info->srq_map.max_count;
	out_params->srq_count = OSAL_BITMAP_WEIGHT(bitmap, nbits);
	out_params->max_srq = nbits;

	bitmap = p_hwfn->p_rdma_info->xrc_srq_map.bitmap;
	nbits = p_hwfn->p_rdma_info->xrc_srq_map.max_count;
	out_params->xrc_srq_count = OSAL_BITMAP_WEIGHT(bitmap, nbits);
	out_params->max_xrc_srq = nbits;

	bitmap = p_hwfn->p_rdma_info->xrcd_map.bitmap;
	nbits = p_hwfn->p_rdma_info->xrcd_map.max_count;
	out_params->xrcd_count = OSAL_BITMAP_WEIGHT(bitmap, nbits);
	out_params->max_xrcd = nbits;

	return ECORE_SUCCESS;
}