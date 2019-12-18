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
struct al_eth_adapter {int num_rx_queues; TYPE_2__* rx_ring; } ;
struct TYPE_3__ {scalar_t__ desc_base; } ;
struct TYPE_4__ {TYPE_1__ q_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_eth_free_rx_resources (struct al_eth_adapter*,int) ; 

__attribute__((used)) static void
al_eth_free_all_rx_resources(struct al_eth_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->num_rx_queues; i++)
		if (adapter->rx_ring[i].q_params.desc_base != 0)
			al_eth_free_rx_resources(adapter, i);
}