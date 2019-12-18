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
struct qlnxr_dev {int /*<<< orphan*/  ibdev; int /*<<< orphan*/  rdma_ctx; int /*<<< orphan*/  dpi; scalar_t__ pd_count; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ERR ; 
 int /*<<< orphan*/  QLNXR_PORT ; 
 scalar_t__ QLNX_IS_IWARP (struct qlnxr_dev*) ; 
 scalar_t__ QLNX_IS_ROCE (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,void*,...) ; 
 int /*<<< orphan*/  ecore_rdma_remove_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_rdma_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnxr_free_resources (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  qlnxr_ib_dispatch_event (struct qlnxr_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_release_irqs (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  qlnxr_remove_sysfiles (struct qlnxr_dev*) ; 

__attribute__((used)) static int
qlnxr_remove(void *eth_dev, void *qlnx_rdma_dev)
{
	struct qlnxr_dev *dev;
	qlnx_host_t *ha;

	dev = qlnx_rdma_dev;
	ha = eth_dev;

	if ((ha == NULL) || (dev == NULL))
		return (0);

	QL_DPRINT12(ha, "enter ha = %p qlnx_rdma_dev = %p pd_count = %d\n",
		ha, qlnx_rdma_dev, dev->pd_count);

	qlnxr_ib_dispatch_event(dev, QLNXR_PORT,
		IB_EVENT_PORT_ERR);

	if (QLNX_IS_IWARP(dev)) {
		if (dev->pd_count)
			return (EBUSY);
	}

	ib_unregister_device(&dev->ibdev);
	
	if (QLNX_IS_ROCE(dev)) {
		if (dev->pd_count)
			return (EBUSY);
	}

	ecore_rdma_remove_user(dev->rdma_ctx, dev->dpi);
	ecore_rdma_stop(dev->rdma_ctx);

	qlnxr_release_irqs(dev);

	qlnxr_free_resources(dev);

	qlnxr_remove_sysfiles(dev);
	ib_dealloc_device(&dev->ibdev);

	QL_DPRINT12(ha, "exit ha = %p qlnx_rdma_dev = %p\n", ha, qlnx_rdma_dev);
	return (0);
}