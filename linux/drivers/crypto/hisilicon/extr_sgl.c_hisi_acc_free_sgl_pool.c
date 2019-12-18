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
struct hisi_acc_sgl_pool {int /*<<< orphan*/  sgl_dma; int /*<<< orphan*/  sgl; int /*<<< orphan*/  size; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hisi_acc_sgl_pool*,int /*<<< orphan*/ ,int) ; 

void hisi_acc_free_sgl_pool(struct device *dev, struct hisi_acc_sgl_pool *pool)
{
	dma_free_coherent(dev, pool->size, pool->sgl, pool->sgl_dma);
	memset(pool, 0, sizeof(struct hisi_acc_sgl_pool));
}