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
struct scatterlist {int /*<<< orphan*/  dma_map; } ;
struct linux_dma_priv {int /*<<< orphan*/  dmat; } ;
struct dma_attrs {int dummy; } ;
struct device {struct linux_dma_priv* dma_priv; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PRIV_LOCK (struct linux_dma_priv*) ; 
 int /*<<< orphan*/  DMA_PRIV_UNLOCK (struct linux_dma_priv*) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
linux_dma_unmap_sg_attrs(struct device *dev, struct scatterlist *sgl,
    int nents, enum dma_data_direction dir, struct dma_attrs *attrs)
{
	struct linux_dma_priv *priv;

	priv = dev->dma_priv;

	DMA_PRIV_LOCK(priv);
	bus_dmamap_unload(priv->dmat, sgl->dma_map);
	bus_dmamap_destroy(priv->dmat, sgl->dma_map);
	DMA_PRIV_UNLOCK(priv);
}