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
struct rdma_srq_producers {int dummy; } ;
struct qlnxr_srq_hwq_info {int /*<<< orphan*/  phy_prod_pair_addr; int /*<<< orphan*/  virt_prod_pair_addr; int /*<<< orphan*/  pbl; } ;
struct qlnxr_srq {struct qlnxr_dev* dev; struct qlnxr_srq_hwq_info hw_srq; } ;
struct qlnxr_dev {int /*<<< orphan*/  cdev; int /*<<< orphan*/ * ha; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ecore_chain_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qlnxr_free_srq_kernel_params(struct qlnxr_srq *srq)
{
	struct qlnxr_srq_hwq_info *hw_srq  = &srq->hw_srq;
	struct qlnxr_dev	*dev = srq->dev;
	qlnx_host_t		*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	ecore_chain_free(dev->cdev, &hw_srq->pbl);

	qlnx_dma_free_coherent(&dev->cdev,
		hw_srq->virt_prod_pair_addr,
		hw_srq->phy_prod_pair_addr,
		sizeof(struct rdma_srq_producers));

	QL_DPRINT12(ha, "exit\n");

	return;
}