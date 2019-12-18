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
struct ep93xx_pata_data {int /*<<< orphan*/ * dma_tx_channel; int /*<<< orphan*/ * dma_rx_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ep93xx_pata_release_dma(struct ep93xx_pata_data *drv_data)
{
	if (drv_data->dma_rx_channel) {
		dma_release_channel(drv_data->dma_rx_channel);
		drv_data->dma_rx_channel = NULL;
	}
	if (drv_data->dma_tx_channel) {
		dma_release_channel(drv_data->dma_tx_channel);
		drv_data->dma_tx_channel = NULL;
	}
}