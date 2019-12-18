#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx4_icm_chunk {int npages; TYPE_3__* mem; } ;
struct mlx4_dev {TYPE_2__* persist; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; } ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lowmem_page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (TYPE_3__*) ; 
 int /*<<< orphan*/  sg_page (TYPE_3__*) ; 

__attribute__((used)) static void mlx4_free_icm_coherent(struct mlx4_dev *dev, struct mlx4_icm_chunk *chunk)
{
	int i;

	for (i = 0; i < chunk->npages; ++i)
		dma_free_coherent(&dev->persist->pdev->dev,
				  chunk->mem[i].length,
				  lowmem_page_address(sg_page(&chunk->mem[i])),
				  sg_dma_address(&chunk->mem[i]));
}