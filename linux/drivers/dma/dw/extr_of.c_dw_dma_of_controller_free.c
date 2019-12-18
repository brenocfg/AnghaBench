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
struct TYPE_2__ {struct device* dev; } ;
struct dw_dma {TYPE_1__ dma; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_dma_controller_free (int /*<<< orphan*/ ) ; 

void dw_dma_of_controller_free(struct dw_dma *dw)
{
	struct device *dev = dw->dma.dev;

	if (!dev->of_node)
		return;

	of_dma_controller_free(dev->of_node);
}