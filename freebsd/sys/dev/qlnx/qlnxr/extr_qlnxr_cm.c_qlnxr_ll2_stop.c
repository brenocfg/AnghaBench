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
struct qlnxr_dev {int gsi_ll2_handle; int /*<<< orphan*/  ha; int /*<<< orphan*/  rdma_ctx; int /*<<< orphan*/  gsi_ll2_mac_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ecore_ll2_release_connection (int /*<<< orphan*/ ,int) ; 
 int ecore_ll2_terminate_connection (int /*<<< orphan*/ ,int) ; 
 int qlnx_rdma_ll2_set_mac_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
qlnxr_ll2_stop(struct qlnxr_dev *dev)
{
	int rc;

	QL_DPRINT12(dev->ha, "enter\n");

	if (dev->gsi_ll2_handle == 0xFF)
		return 0;

	/* remove LL2 MAC address filter */
	rc = qlnx_rdma_ll2_set_mac_filter(dev->rdma_ctx,
			  dev->gsi_ll2_mac_address, NULL);

	rc = ecore_ll2_terminate_connection(dev->rdma_ctx,
			dev->gsi_ll2_handle);

	ecore_ll2_release_connection(dev->rdma_ctx, dev->gsi_ll2_handle);

	dev->gsi_ll2_handle = 0xFF;

	QL_DPRINT12(dev->ha, "exit rc = %d\n", rc);
	return rc;
}