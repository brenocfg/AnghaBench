#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx4_icm_chunk {size_t npages; scalar_t__ nsg; int /*<<< orphan*/ * mem; int /*<<< orphan*/  list; } ;
struct mlx4_icm {int /*<<< orphan*/  chunk_list; scalar_t__ refcount; } ;
struct mlx4_dev {TYPE_1__* persist; int /*<<< orphan*/  numa_node; } ;
typedef  int gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {TYPE_2__* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX4_ICM_ALLOC_SIZE ; 
 size_t MLX4_ICM_CHUNK_LEN ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int __GFP_HIGHMEM ; 
 int __GFP_NOWARN ; 
 int get_order (int /*<<< orphan*/ ) ; 
 void* kmalloc (int,int) ; 
 void* kmalloc_node (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlx4_alloc_icm_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int mlx4_alloc_icm_pages (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_icm (struct mlx4_dev*,struct mlx4_icm*,int) ; 
 void* pci_map_sg (TYPE_2__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,size_t) ; 

struct mlx4_icm *mlx4_alloc_icm(struct mlx4_dev *dev, int npages,
				gfp_t gfp_mask, int coherent)
{
	struct mlx4_icm *icm;
	struct mlx4_icm_chunk *chunk = NULL;
	int cur_order;
	int ret;

	/* We use sg_set_buf for coherent allocs, which assumes low memory */
	BUG_ON(coherent && (gfp_mask & __GFP_HIGHMEM));

	icm = kmalloc_node(sizeof(*icm),
			   gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWARN),
			   dev->numa_node);
	if (!icm) {
		icm = kmalloc(sizeof(*icm),
			      gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWARN));
		if (!icm)
			return NULL;
	}

	icm->refcount = 0;
	INIT_LIST_HEAD(&icm->chunk_list);

	cur_order = get_order(MLX4_ICM_ALLOC_SIZE);

	while (npages > 0) {
		if (!chunk) {
			chunk = kmalloc_node(sizeof(*chunk),
					     gfp_mask & ~(__GFP_HIGHMEM |
							  __GFP_NOWARN),
					     dev->numa_node);
			if (!chunk) {
				chunk = kmalloc(sizeof(*chunk),
						gfp_mask & ~(__GFP_HIGHMEM |
							     __GFP_NOWARN));
				if (!chunk)
					goto fail;
			}

			sg_init_table(chunk->mem, MLX4_ICM_CHUNK_LEN);
			chunk->npages = 0;
			chunk->nsg    = 0;
			list_add_tail(&chunk->list, &icm->chunk_list);
		}

		while (1 << cur_order > npages)
			--cur_order;

		if (coherent)
			ret = mlx4_alloc_icm_coherent(&dev->persist->pdev->dev,
						      &chunk->mem[chunk->npages],
						      cur_order, gfp_mask);
		else
			ret = mlx4_alloc_icm_pages(&chunk->mem[chunk->npages],
						   cur_order, gfp_mask,
						   dev->numa_node);

		if (ret) {
			if (--cur_order < 0)
				goto fail;
			else
				continue;
		}

		++chunk->npages;

		if (coherent)
			++chunk->nsg;
		else if (chunk->npages == MLX4_ICM_CHUNK_LEN) {
			chunk->nsg = pci_map_sg(dev->persist->pdev, chunk->mem,
						chunk->npages,
						PCI_DMA_BIDIRECTIONAL);

			if (chunk->nsg <= 0)
				goto fail;
		}

		if (chunk->npages == MLX4_ICM_CHUNK_LEN)
			chunk = NULL;

		npages -= 1 << cur_order;
	}

	if (!coherent && chunk) {
		chunk->nsg = pci_map_sg(dev->persist->pdev, chunk->mem,
					chunk->npages,
					PCI_DMA_BIDIRECTIONAL);

		if (chunk->nsg <= 0)
			goto fail;
	}

	return icm;

fail:
	mlx4_free_icm(dev, icm, coherent);
	return NULL;
}