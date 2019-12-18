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
struct ena_adapter {int num_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  ena_free_tx_bufs (struct ena_adapter*,int) ; 

__attribute__((used)) static void
ena_free_all_tx_bufs(struct ena_adapter *adapter)
{

	for (int i = 0; i < adapter->num_queues; i++)
		ena_free_tx_bufs(adapter, i);
}