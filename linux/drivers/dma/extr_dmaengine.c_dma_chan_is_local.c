#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NUMA_NO_NODE ; 
 int /*<<< orphan*/  cpumask_of_node (int) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int dev_to_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dma_chan_is_local(struct dma_chan *chan, int cpu)
{
	int node = dev_to_node(chan->device->dev);
	return node == NUMA_NO_NODE ||
		cpumask_test_cpu(cpu, cpumask_of_node(node));
}