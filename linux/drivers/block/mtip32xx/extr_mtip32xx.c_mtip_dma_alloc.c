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
struct mtip_port {int block1_dma; int command_list_dma; int rxfis_dma; int identify_dma; int log_buf_dma; int smart_buf_dma; int /*<<< orphan*/ * block1; int /*<<< orphan*/ * smart_buf; int /*<<< orphan*/ * log_buf; int /*<<< orphan*/ * identify; int /*<<< orphan*/ * rxfis; void* command_list; } ;
struct driver_data {TYPE_1__* pdev; struct mtip_port* port; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_CMD_TBL_SZ ; 
 int AHCI_IDFY_OFFSET ; 
 int AHCI_RX_FIS_OFFSET ; 
 int AHCI_SECTBUF_OFFSET ; 
 int AHCI_SMARTBUF_OFFSET ; 
 int /*<<< orphan*/  BLOCK_DMA_ALLOC_SZ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mtip_dma_alloc(struct driver_data *dd)
{
	struct mtip_port *port = dd->port;

	/* Allocate dma memory for RX Fis, Identify, and Sector Bufffer */
	port->block1 =
		dma_alloc_coherent(&dd->pdev->dev, BLOCK_DMA_ALLOC_SZ,
					&port->block1_dma, GFP_KERNEL);
	if (!port->block1)
		return -ENOMEM;

	/* Allocate dma memory for command list */
	port->command_list =
		dma_alloc_coherent(&dd->pdev->dev, AHCI_CMD_TBL_SZ,
					&port->command_list_dma, GFP_KERNEL);
	if (!port->command_list) {
		dma_free_coherent(&dd->pdev->dev, BLOCK_DMA_ALLOC_SZ,
					port->block1, port->block1_dma);
		port->block1 = NULL;
		port->block1_dma = 0;
		return -ENOMEM;
	}

	/* Setup all pointers into first DMA region */
	port->rxfis         = port->block1 + AHCI_RX_FIS_OFFSET;
	port->rxfis_dma     = port->block1_dma + AHCI_RX_FIS_OFFSET;
	port->identify      = port->block1 + AHCI_IDFY_OFFSET;
	port->identify_dma  = port->block1_dma + AHCI_IDFY_OFFSET;
	port->log_buf       = port->block1 + AHCI_SECTBUF_OFFSET;
	port->log_buf_dma   = port->block1_dma + AHCI_SECTBUF_OFFSET;
	port->smart_buf     = port->block1 + AHCI_SMARTBUF_OFFSET;
	port->smart_buf_dma = port->block1_dma + AHCI_SMARTBUF_OFFSET;

	return 0;
}