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
struct hash_platform_data {int /*<<< orphan*/  dma_filter; int /*<<< orphan*/  mem_to_engine; } ;
struct TYPE_2__ {int /*<<< orphan*/  complete; int /*<<< orphan*/  chan_mem2hash; int /*<<< orphan*/  cfg_mem2hash; int /*<<< orphan*/  mask; } ;
struct hash_device_data {TYPE_1__ dma; scalar_t__ phybase; } ;
struct dma_slave_config {int dst_maxburst; int /*<<< orphan*/  dst_addr_width; scalar_t__ dst_addr; int /*<<< orphan*/  direction; } ;
struct device {struct hash_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 scalar_t__ HASH_DMA_FIFO ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_slave_config (int /*<<< orphan*/ ,struct dma_slave_config*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hash_dma_setup_channel(struct hash_device_data *device_data,
				   struct device *dev)
{
	struct hash_platform_data *platform_data = dev->platform_data;
	struct dma_slave_config conf = {
		.direction = DMA_MEM_TO_DEV,
		.dst_addr = device_data->phybase + HASH_DMA_FIFO,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES,
		.dst_maxburst = 16,
	};

	dma_cap_zero(device_data->dma.mask);
	dma_cap_set(DMA_SLAVE, device_data->dma.mask);

	device_data->dma.cfg_mem2hash = platform_data->mem_to_engine;
	device_data->dma.chan_mem2hash =
		dma_request_channel(device_data->dma.mask,
				    platform_data->dma_filter,
				    device_data->dma.cfg_mem2hash);

	dmaengine_slave_config(device_data->dma.chan_mem2hash, &conf);

	init_completion(&device_data->dma.complete);
}