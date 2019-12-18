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
struct ix_rx_queue {int /*<<< orphan*/  irqs; int /*<<< orphan*/  msix; struct adapter* adapter; } ;
struct ifnet {int if_drv_flags; } ;
struct adapter {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int FILTER_SCHEDULE_THREAD ; 
 int IFF_DRV_RUNNING ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_disable_queue (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixgbe_msix_que(void *arg)
{
	struct ix_rx_queue *que = arg;
	struct adapter     *adapter = que->adapter;
	struct ifnet       *ifp = iflib_get_ifp(que->adapter->ctx);

	/* Protect against spurious interrupts */
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return (FILTER_HANDLED);

	ixgbe_disable_queue(adapter, que->msix);
	++que->irqs;

	return (FILTER_SCHEDULE_THREAD);
}