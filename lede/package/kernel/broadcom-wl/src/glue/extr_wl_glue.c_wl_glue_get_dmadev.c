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
struct ssb_device {struct device* dma_dev; } ;
struct device {int dummy; } ;
struct bcma_device {struct device* dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  WL_GLUE_BUS_TYPE_BCMA 129 
#define  WL_GLUE_BUS_TYPE_SSB 128 
 int active_bus_type ; 

struct device * wl_glue_get_dmadev(void *dev)
{
	struct device *dma_dev;

	switch (active_bus_type)
	{
#ifdef CONFIG_SSB
	case WL_GLUE_BUS_TYPE_SSB:
		dma_dev = ((struct ssb_device *)dev)->dma_dev;
		break;
#endif /* CONFIG_SSB */

#ifdef CONFIG_BCMA
	case WL_GLUE_BUS_TYPE_BCMA:
		dma_dev = ((struct bcma_device *)dev)->dma_dev;
		break;
#endif /* CONFIG_BCMA */

	default:
		BUG();
		dma_dev = NULL;
		break;
	}

	return dma_dev;
}