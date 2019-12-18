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
struct device {int /*<<< orphan*/  of_node; struct device* parent; } ;

/* Variables and functions */
 scalar_t__ dev_is_fsl_mc (struct device*) ; 
 int of_dma_configure (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_mc_dma_configure(struct device *dev)
{
	struct device *dma_dev = dev;

	while (dev_is_fsl_mc(dma_dev))
		dma_dev = dma_dev->parent;

	return of_dma_configure(dev, dma_dev->of_node, 0);
}