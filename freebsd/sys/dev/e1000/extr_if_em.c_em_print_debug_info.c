#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tx_ring {int dummy; } ;
struct rx_ring {int dummy; } ;
struct ifnet {int dummy; } ;
struct adapter {int tx_num_queues; int rx_num_queues; int /*<<< orphan*/  hw; TYPE_2__* rx_queues; TYPE_1__* tx_queues; int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {struct rx_ring rxr; } ;
struct TYPE_3__ {struct tx_ring txr; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RDH (int) ; 
 int /*<<< orphan*/  E1000_RDT (int) ; 
 int /*<<< orphan*/  E1000_READ_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_TDH (int) ; 
 int /*<<< orphan*/  E1000_TDT (int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int if_getdrvflags (struct ifnet*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
em_print_debug_info(struct adapter *adapter)
{
	device_t dev = iflib_get_dev(adapter->ctx);
	struct ifnet *ifp = iflib_get_ifp(adapter->ctx);
	struct tx_ring *txr = &adapter->tx_queues->txr;
	struct rx_ring *rxr = &adapter->rx_queues->rxr;

	if (if_getdrvflags(ifp) & IFF_DRV_RUNNING)
		printf("Interface is RUNNING ");
	else
		printf("Interface is NOT RUNNING\n");

	if (if_getdrvflags(ifp) & IFF_DRV_OACTIVE)
		printf("and INACTIVE\n");
	else
		printf("and ACTIVE\n");

	for (int i = 0; i < adapter->tx_num_queues; i++, txr++) {
		device_printf(dev, "TX Queue %d ------\n", i);
		device_printf(dev, "hw tdh = %d, hw tdt = %d\n",
			E1000_READ_REG(&adapter->hw, E1000_TDH(i)),
			E1000_READ_REG(&adapter->hw, E1000_TDT(i)));

	}
	for (int j=0; j < adapter->rx_num_queues; j++, rxr++) {
		device_printf(dev, "RX Queue %d ------\n", j);
		device_printf(dev, "hw rdh = %d, hw rdt = %d\n",
			E1000_READ_REG(&adapter->hw, E1000_RDH(j)),
			E1000_READ_REG(&adapter->hw, E1000_RDT(j)));
	}
}