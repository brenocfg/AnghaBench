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
struct ecore_rdma_device {int /*<<< orphan*/  max_qp_req_rd_atomic_resc; int /*<<< orphan*/  max_qp_resp_rd_atomic_resc; scalar_t__ max_qp; scalar_t__ max_cq; int /*<<< orphan*/  max_inline; } ;
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_qps; struct ecore_rdma_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_IWARP_IRD_DEFAULT ; 
 int /*<<< orphan*/  ECORE_IWARP_ORD_DEFAULT ; 
 scalar_t__ ECORE_IWARP_PREALLOC_CNT ; 
 int /*<<< orphan*/  IWARP_MAX_QPS ; 
 int /*<<< orphan*/  IWARP_REQ_MAX_INLINE_DATA_SIZE ; 
 scalar_t__ OSAL_MIN_T (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64 ; 

void
ecore_iwarp_init_devinfo(struct ecore_hwfn *p_hwfn)
{
	struct ecore_rdma_device *dev = p_hwfn->p_rdma_info->dev;

	dev->max_inline = IWARP_REQ_MAX_INLINE_DATA_SIZE;
	dev->max_qp = OSAL_MIN_T(u64,
				 IWARP_MAX_QPS,
				 p_hwfn->p_rdma_info->num_qps) -
		ECORE_IWARP_PREALLOC_CNT;

	dev->max_cq = dev->max_qp;

	dev->max_qp_resp_rd_atomic_resc = ECORE_IWARP_IRD_DEFAULT;
	dev->max_qp_req_rd_atomic_resc = ECORE_IWARP_ORD_DEFAULT;
}