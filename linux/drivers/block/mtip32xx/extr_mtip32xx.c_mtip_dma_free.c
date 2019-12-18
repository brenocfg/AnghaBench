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
struct mtip_port {int /*<<< orphan*/  command_list_dma; scalar_t__ command_list; int /*<<< orphan*/  block1_dma; scalar_t__ block1; } ;
struct driver_data {TYPE_1__* pdev; struct mtip_port* port; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_CMD_TBL_SZ ; 
 int /*<<< orphan*/  BLOCK_DMA_ALLOC_SZ ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtip_dma_free(struct driver_data *dd)
{
	struct mtip_port *port = dd->port;

	if (port->block1)
		dma_free_coherent(&dd->pdev->dev, BLOCK_DMA_ALLOC_SZ,
					port->block1, port->block1_dma);

	if (port->command_list) {
		dma_free_coherent(&dd->pdev->dev, AHCI_CMD_TBL_SZ,
				port->command_list, port->command_list_dma);
	}
}