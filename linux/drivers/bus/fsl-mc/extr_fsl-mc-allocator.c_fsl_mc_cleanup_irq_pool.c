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
struct fsl_mc_resource_pool {scalar_t__ max_count; scalar_t__ free_count; int /*<<< orphan*/  free_list; } ;
struct fsl_mc_device {int /*<<< orphan*/  dev; } ;
struct fsl_mc_bus {int /*<<< orphan*/ * irq_resources; struct fsl_mc_resource_pool* resource_pools; struct fsl_mc_device mc_dev; } ;

/* Variables and functions */
 size_t FSL_MC_POOL_IRQ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_mc_msi_domain_free_irqs (int /*<<< orphan*/ *) ; 

void fsl_mc_cleanup_irq_pool(struct fsl_mc_bus *mc_bus)
{
	struct fsl_mc_device *mc_bus_dev = &mc_bus->mc_dev;
	struct fsl_mc_resource_pool *res_pool =
			&mc_bus->resource_pools[FSL_MC_POOL_IRQ];

	if (!mc_bus->irq_resources)
		return;

	if (res_pool->max_count == 0)
		return;

	if (res_pool->free_count != res_pool->max_count)
		return;

	INIT_LIST_HEAD(&res_pool->free_list);
	res_pool->max_count = 0;
	res_pool->free_count = 0;
	mc_bus->irq_resources = NULL;
	fsl_mc_msi_domain_free_irqs(&mc_bus_dev->dev);
}