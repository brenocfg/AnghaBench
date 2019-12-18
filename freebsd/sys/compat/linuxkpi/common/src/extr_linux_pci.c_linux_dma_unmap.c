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
struct linux_dma_priv {int /*<<< orphan*/  dmat; int /*<<< orphan*/  ptree; } ;
struct linux_dma_obj {int /*<<< orphan*/  dmamap; } ;
struct device {struct linux_dma_priv* dma_priv; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PRIV_LOCK (struct linux_dma_priv*) ; 
 int /*<<< orphan*/  DMA_PRIV_UNLOCK (struct linux_dma_priv*) ; 
 struct linux_dma_obj* LINUX_DMA_PCTRIE_LOOKUP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINUX_DMA_PCTRIE_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_dma_obj_zone ; 
 scalar_t__ pctrie_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct linux_dma_obj*) ; 

void
linux_dma_unmap(struct device *dev, dma_addr_t dma_addr, size_t len)
{
	struct linux_dma_priv *priv;
	struct linux_dma_obj *obj;

	priv = dev->dma_priv;

	if (pctrie_is_empty(&priv->ptree))
		return;

	DMA_PRIV_LOCK(priv);
	obj = LINUX_DMA_PCTRIE_LOOKUP(&priv->ptree, dma_addr);
	if (obj == NULL) {
		DMA_PRIV_UNLOCK(priv);
		return;
	}
	LINUX_DMA_PCTRIE_REMOVE(&priv->ptree, dma_addr);
	bus_dmamap_unload(priv->dmat, obj->dmamap);
	bus_dmamap_destroy(priv->dmat, obj->dmamap);
	DMA_PRIV_UNLOCK(priv);

	uma_zfree(linux_dma_obj_zone, obj);
}