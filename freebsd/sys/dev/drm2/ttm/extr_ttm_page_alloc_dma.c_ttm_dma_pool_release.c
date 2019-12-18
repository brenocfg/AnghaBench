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
struct dma_pool {int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_dma_free_pool (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttm_dma_pool_release(struct device *dev, void *res)
{
	struct dma_pool *pool = *(struct dma_pool **)res;

	if (pool)
		ttm_dma_free_pool(dev, pool->type);
}