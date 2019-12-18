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
typedef  int /*<<< orphan*/  uint8_t ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;

/* Variables and functions */
 int IB_LINK_LAYER_ETHERNET ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,struct ib_device*,int /*<<< orphan*/ ) ; 
 struct qlnxr_dev* get_qlnxr_dev (struct ib_device*) ; 

enum rdma_link_layer
qlnxr_link_layer(struct ib_device *ibdev, uint8_t port_num)
{
	struct qlnxr_dev	*dev;
	qlnx_host_t		*ha;

	dev = get_qlnxr_dev(ibdev);
	ha = dev->ha;

	QL_DPRINT12(ha, "ibdev = %p port_num = 0x%x\n", ibdev, port_num);

        return IB_LINK_LAYER_ETHERNET;
}