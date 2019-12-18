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
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/ * bus_dma_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_GET_DMA_TAG (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 

bus_dma_tag_t
bus_get_dma_tag(device_t dev)
{
	device_t parent;

	parent = device_get_parent(dev);
	if (parent == NULL)
		return (NULL);
	return (BUS_GET_DMA_TAG(parent, dev));
}