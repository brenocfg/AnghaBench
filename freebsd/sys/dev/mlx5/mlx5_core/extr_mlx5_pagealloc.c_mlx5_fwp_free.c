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
struct mlx5_fw_page {unsigned int numpages; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  virt_addr; struct mlx5_core_dev* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_tag; } ;
struct mlx5_core_dev {TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_fw_page*) ; 

void
mlx5_fwp_free(struct mlx5_fw_page *fwp)
{
	struct mlx5_core_dev *dev;
	unsigned num;

	/* be NULL safe */
	if (fwp == NULL)
		return;

	/* check for special case */
	if (fwp->numpages == 0) {
		kfree(fwp);
		return;
	}

	num = fwp->numpages;
	dev = fwp->dev;

	while (num--) {
		bus_dmamap_unload(dev->cmd.dma_tag, fwp[num].dma_map);
		bus_dmamem_free(dev->cmd.dma_tag, fwp[num].virt_addr, fwp[num].dma_map);
	}

	kfree(fwp);
}