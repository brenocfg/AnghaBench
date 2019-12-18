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
struct netfront_info {unsigned long num_queues; TYPE_1__* txq; TYPE_2__* rxq; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  xen_intr_handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  xen_intr_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  destroy_rxqs (struct netfront_info*) ; 
 int /*<<< orphan*/  destroy_txqs (struct netfront_info*) ; 
 int setup_rxqs (int /*<<< orphan*/ ,struct netfront_info*,unsigned long) ; 
 int setup_txqs (int /*<<< orphan*/ ,struct netfront_info*,unsigned long) ; 

__attribute__((used)) static int
setup_device(device_t dev, struct netfront_info *info,
    unsigned long num_queues)
{
	int error;
	int q;

	if (info->txq)
		destroy_txqs(info);

	if (info->rxq)
		destroy_rxqs(info);

	info->num_queues = 0;

	error = setup_rxqs(dev, info, num_queues);
	if (error != 0)
		goto out;
	error = setup_txqs(dev, info, num_queues);
	if (error != 0)
		goto out;

	info->num_queues = num_queues;

	/* No split event channel at the moment. */
	for (q = 0; q < num_queues; q++)
		info->rxq[q].xen_intr_handle = info->txq[q].xen_intr_handle;

	return (0);

out:
	KASSERT(error != 0, ("Error path taken without providing an error code"));
	return (error);
}