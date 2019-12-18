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
struct ena_adapter {int num_queues; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ena_free_rx_resources (struct ena_adapter*,int) ; 
 int ena_setup_rx_resources (struct ena_adapter*,int) ; 

__attribute__((used)) static int
ena_setup_all_rx_resources(struct ena_adapter *adapter)
{
	int i, rc = 0;

	for (i = 0; i < adapter->num_queues; i++) {
		rc = ena_setup_rx_resources(adapter, i);
		if (rc != 0) {
			device_printf(adapter->pdev,
			    "Allocation for Rx Queue %u failed\n", i);
			goto err_setup_rx;
		}
	}
	return (0);

err_setup_rx:
	/* rewind the index freeing the rings as we go */
	while (i--)
		ena_free_rx_resources(adapter, i);
	return (rc);
}