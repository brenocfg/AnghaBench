#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
typedef  int /*<<< orphan*/ * bus_dma_tag_t ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_GET_DMA_TAG (int /*<<< orphan*/ *,TYPE_1__*) ; 

bus_dma_tag_t
bus_generic_get_dma_tag(device_t dev, device_t child)
{

	/* Propagate up the bus hierarchy until someone handles it. */
	if (dev->parent != NULL)
		return (BUS_GET_DMA_TAG(dev->parent, child));
	return (NULL);
}