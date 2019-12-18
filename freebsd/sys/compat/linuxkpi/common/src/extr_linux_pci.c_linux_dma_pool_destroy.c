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
struct dma_pool {int /*<<< orphan*/  pool_lock; int /*<<< orphan*/  pool_dmat; int /*<<< orphan*/  pool_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dma_pool*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

void
linux_dma_pool_destroy(struct dma_pool *pool)
{

	uma_zdestroy(pool->pool_zone);
	bus_dma_tag_destroy(pool->pool_dmat);
	mtx_destroy(&pool->pool_lock);
	kfree(pool);
}