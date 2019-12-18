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
struct mlx5_fw_page {unsigned int numpages; int /*<<< orphan*/  dma_map; TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_tag; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mlx5_fwp_invalidate(struct mlx5_fw_page *fwp)
{
	unsigned num = fwp->numpages;

	while (num--) {
		bus_dmamap_sync(fwp[num].dev->cmd.dma_tag, fwp[num].dma_map, BUS_DMASYNC_POSTREAD);
		bus_dmamap_sync(fwp[num].dev->cmd.dma_tag, fwp[num].dma_map, BUS_DMASYNC_PREREAD);
	}
}