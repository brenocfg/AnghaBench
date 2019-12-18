#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx4_icm_chunk {scalar_t__ nsg; int npages; TYPE_2__* mem; } ;
struct mlx4_dev {TYPE_1__* persist; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;
struct TYPE_4__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_sg (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (TYPE_2__*) ; 

__attribute__((used)) static void mlx4_free_icm_pages(struct mlx4_dev *dev, struct mlx4_icm_chunk *chunk)
{
	int i;

	if (chunk->nsg > 0)
		pci_unmap_sg(dev->persist->pdev, chunk->mem, chunk->npages,
			     PCI_DMA_BIDIRECTIONAL);

	for (i = 0; i < chunk->npages; ++i)
		__free_pages(sg_page(&chunk->mem[i]),
			     get_order(chunk->mem[i].length));
}