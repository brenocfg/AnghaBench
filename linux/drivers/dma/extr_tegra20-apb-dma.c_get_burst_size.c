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
typedef  int u32 ;
struct tegra_dma_channel {int dummy; } ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
 int TEGRA_APBDMA_AHBSEQ_BURST_1 ; 
 int TEGRA_APBDMA_AHBSEQ_BURST_4 ; 
 int TEGRA_APBDMA_AHBSEQ_BURST_8 ; 

__attribute__((used)) static inline int get_burst_size(struct tegra_dma_channel *tdc,
	u32 burst_size, enum dma_slave_buswidth slave_bw, int len)
{
	int burst_byte;
	int burst_ahb_width;

	/*
	 * burst_size from client is in terms of the bus_width.
	 * convert them into AHB memory width which is 4 byte.
	 */
	burst_byte = burst_size * slave_bw;
	burst_ahb_width = burst_byte / 4;

	/* If burst size is 0 then calculate the burst size based on length */
	if (!burst_ahb_width) {
		if (len & 0xF)
			return TEGRA_APBDMA_AHBSEQ_BURST_1;
		else if ((len >> 4) & 0x1)
			return TEGRA_APBDMA_AHBSEQ_BURST_4;
		else
			return TEGRA_APBDMA_AHBSEQ_BURST_8;
	}
	if (burst_ahb_width < 4)
		return TEGRA_APBDMA_AHBSEQ_BURST_1;
	else if (burst_ahb_width < 8)
		return TEGRA_APBDMA_AHBSEQ_BURST_4;
	else
		return TEGRA_APBDMA_AHBSEQ_BURST_8;
}