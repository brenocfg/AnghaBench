#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct linux_dma_priv {int /*<<< orphan*/  dmat; int /*<<< orphan*/  ptree; } ;
struct linux_dma_obj {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  dmamap; } ;
struct device {struct linux_dma_priv* dma_priv; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  DMA_PRIV_LOCK (struct linux_dma_priv*) ; 
 int /*<<< orphan*/  DMA_PRIV_UNLOCK (struct linux_dma_priv*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LINUX_DMA_PCTRIE_INSERT (int /*<<< orphan*/ *,struct linux_dma_obj*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ _bus_dmamap_load_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 scalar_t__ bus_dma_id_mapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_dma_obj_zone ; 
 struct linux_dma_obj* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct linux_dma_obj*) ; 

dma_addr_t
linux_dma_map_phys(struct device *dev, vm_paddr_t phys, size_t len)
{
	struct linux_dma_priv *priv;
	struct linux_dma_obj *obj;
	int error, nseg;
	bus_dma_segment_t seg;

	priv = dev->dma_priv;

	/*
	 * If the resultant mapping will be entirely 1:1 with the
	 * physical address, short-circuit the remainder of the
	 * bus_dma API.  This avoids tracking collisions in the pctrie
	 * with the additional benefit of reducing overhead.
	 */
	if (bus_dma_id_mapped(priv->dmat, phys, len))
		return (phys);

	obj = uma_zalloc(linux_dma_obj_zone, M_NOWAIT);
	if (obj == NULL) {
		return (0);
	}

	DMA_PRIV_LOCK(priv);
	if (bus_dmamap_create(priv->dmat, 0, &obj->dmamap) != 0) {
		DMA_PRIV_UNLOCK(priv);
		uma_zfree(linux_dma_obj_zone, obj);
		return (0);
	}

	nseg = -1;
	if (_bus_dmamap_load_phys(priv->dmat, obj->dmamap, phys, len,
	    BUS_DMA_NOWAIT, &seg, &nseg) != 0) {
		bus_dmamap_destroy(priv->dmat, obj->dmamap);
		DMA_PRIV_UNLOCK(priv);
		uma_zfree(linux_dma_obj_zone, obj);
		return (0);
	}

	KASSERT(++nseg == 1, ("More than one segment (nseg=%d)", nseg));
	obj->dma_addr = seg.ds_addr;

	error = LINUX_DMA_PCTRIE_INSERT(&priv->ptree, obj);
	if (error != 0) {
		bus_dmamap_unload(priv->dmat, obj->dmamap);
		bus_dmamap_destroy(priv->dmat, obj->dmamap);
		DMA_PRIV_UNLOCK(priv);
		uma_zfree(linux_dma_obj_zone, obj);
		return (0);
	}
	DMA_PRIV_UNLOCK(priv);
	return (obj->dma_addr);
}