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
struct TYPE_2__ {unsigned long dst_addr; int dst_addr_width; unsigned int dst_maxburst; unsigned long src_addr; int src_addr_width; unsigned int src_maxburst; } ;
struct tegra_dma_channel {TYPE_1__ dma_sconfig; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
#define  DMA_DEV_TO_MEM 129 
#define  DMA_MEM_TO_DEV 128 
 int EINVAL ; 
 unsigned long TEGRA_APBDMA_CSR_DIR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long get_bus_width (struct tegra_dma_channel*,int) ; 
 int /*<<< orphan*/  tdc2dev (struct tegra_dma_channel*) ; 

__attribute__((used)) static int get_transfer_param(struct tegra_dma_channel *tdc,
	enum dma_transfer_direction direction, unsigned long *apb_addr,
	unsigned long *apb_seq,	unsigned long *csr, unsigned int *burst_size,
	enum dma_slave_buswidth *slave_bw)
{
	switch (direction) {
	case DMA_MEM_TO_DEV:
		*apb_addr = tdc->dma_sconfig.dst_addr;
		*apb_seq = get_bus_width(tdc, tdc->dma_sconfig.dst_addr_width);
		*burst_size = tdc->dma_sconfig.dst_maxburst;
		*slave_bw = tdc->dma_sconfig.dst_addr_width;
		*csr = TEGRA_APBDMA_CSR_DIR;
		return 0;

	case DMA_DEV_TO_MEM:
		*apb_addr = tdc->dma_sconfig.src_addr;
		*apb_seq = get_bus_width(tdc, tdc->dma_sconfig.src_addr_width);
		*burst_size = tdc->dma_sconfig.src_maxburst;
		*slave_bw = tdc->dma_sconfig.src_addr_width;
		*csr = 0;
		return 0;

	default:
		dev_err(tdc2dev(tdc), "DMA direction is not supported\n");
		return -EINVAL;
	}
	return -EINVAL;
}