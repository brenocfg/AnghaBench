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
struct mlx5_fw_page {unsigned int numpages; scalar_t__ load_done; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  virt_addr; struct mlx5_core_dev* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_sx; int /*<<< orphan*/  dma_tag; } ;
struct mlx5_core_dev {TYPE_1__ cmd; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int /*<<< orphan*/  MLX5_ADAPTER_PAGE_SIZE ; 
 int /*<<< orphan*/  MLX5_DMA_LOCK (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  MLX5_DMA_UNLOCK (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  MLX5_DMA_WAIT (struct mlx5_core_dev*) ; 
 scalar_t__ MLX5_LOAD_ST_NONE ; 
 scalar_t__ MLX5_LOAD_ST_SUCCESS ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlx5_fw_page*,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_fw_page*) ; 
 struct mlx5_fw_page* kzalloc (int,int) ; 
 int /*<<< orphan*/  mlx5_fwp_load_mem_cb ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

struct mlx5_fw_page *
mlx5_fwp_alloc(struct mlx5_core_dev *dev, gfp_t flags, unsigned num)
{
	struct mlx5_fw_page *fwp;
	unsigned x;
	int err;

	/* check for special case */
	if (num == 0) {
		fwp = kzalloc(sizeof(*fwp), flags);
		if (fwp != NULL)
			fwp->dev = dev;
		return (fwp);
	}

	/* we need sleeping context for this function */
	if (flags & M_NOWAIT)
		return (NULL);

	fwp = kzalloc(sizeof(*fwp) * num, flags);

	/* serialize loading the DMA map(s) */
	sx_xlock(&dev->cmd.dma_sx);

	for (x = 0; x != num; x++) {
		/* store pointer to MLX5 core device */
		fwp[x].dev = dev;
		/* store number of pages left from the array */
		fwp[x].numpages = num - x;

		/* allocate memory */
		err = bus_dmamem_alloc(dev->cmd.dma_tag, &fwp[x].virt_addr,
		    BUS_DMA_WAITOK | BUS_DMA_COHERENT, &fwp[x].dma_map);
		if (err != 0)
			goto failure;

		/* load memory into DMA */
		MLX5_DMA_LOCK(dev);
		(void) bus_dmamap_load(
		    dev->cmd.dma_tag, fwp[x].dma_map, fwp[x].virt_addr,
		    MLX5_ADAPTER_PAGE_SIZE, &mlx5_fwp_load_mem_cb,
		    fwp + x, BUS_DMA_WAITOK | BUS_DMA_COHERENT);

		while (fwp[x].load_done == MLX5_LOAD_ST_NONE)
			MLX5_DMA_WAIT(dev);
		MLX5_DMA_UNLOCK(dev);

		/* check for error */
		if (fwp[x].load_done != MLX5_LOAD_ST_SUCCESS) {
			bus_dmamem_free(dev->cmd.dma_tag, fwp[x].virt_addr,
			    fwp[x].dma_map);
			goto failure;
		}
	}
	sx_xunlock(&dev->cmd.dma_sx);
	return (fwp);

failure:
	while (x--) {
		bus_dmamap_unload(dev->cmd.dma_tag, fwp[x].dma_map);
		bus_dmamem_free(dev->cmd.dma_tag, fwp[x].virt_addr, fwp[x].dma_map);
	}
	sx_xunlock(&dev->cmd.dma_sx);
	kfree(fwp);
	return (NULL);
}