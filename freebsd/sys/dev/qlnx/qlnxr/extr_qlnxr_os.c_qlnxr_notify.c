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
struct qlnxr_dev {int /*<<< orphan*/  enet_state; int /*<<< orphan*/ * ha; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
typedef  enum qlnx_rdma_event { ____Placeholder_qlnx_rdma_event } qlnx_rdma_event ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ERR ; 
 int /*<<< orphan*/  QLNXR_ENET_STATE_BIT ; 
 int /*<<< orphan*/  QLNXR_PORT ; 
#define  QLNX_ETHDEV_CHANGE_ADDR 130 
#define  QLNX_ETHDEV_DOWN 129 
#define  QLNX_ETHDEV_UP 128 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,void*,int) ; 
 int /*<<< orphan*/  qlnxr_ib_dispatch_event (struct qlnxr_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_mac_address_change (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlnxr_notify(void *eth_dev, void *qlnx_rdma_dev, enum qlnx_rdma_event event)
{
	struct qlnxr_dev *dev;
	qlnx_host_t *ha;

	dev = qlnx_rdma_dev;

	if (dev == NULL)
		return;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter (%p, %d)\n", qlnx_rdma_dev, event);

        switch (event) {

        case QLNX_ETHDEV_UP:
		if (!test_and_set_bit(QLNXR_ENET_STATE_BIT, &dev->enet_state))
			qlnxr_ib_dispatch_event(dev, QLNXR_PORT,
				IB_EVENT_PORT_ACTIVE);
                break;

        case QLNX_ETHDEV_CHANGE_ADDR:
                qlnxr_mac_address_change(dev);
                break;

        case QLNX_ETHDEV_DOWN:
		if (test_and_set_bit(QLNXR_ENET_STATE_BIT, &dev->enet_state))
			qlnxr_ib_dispatch_event(dev, QLNXR_PORT,
				IB_EVENT_PORT_ERR);
                break;
        }

	QL_DPRINT12(ha, "exit (%p, %d)\n", qlnx_rdma_dev, event);
	return;
}