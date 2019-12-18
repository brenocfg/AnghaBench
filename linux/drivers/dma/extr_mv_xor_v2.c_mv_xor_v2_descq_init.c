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
struct mv_xor_v2_device {scalar_t__ dma_base; scalar_t__ glob_base; int /*<<< orphan*/  hw_desq; } ;

/* Variables and functions */
 int MV_XOR_V2_DESC_NUM ; 
 scalar_t__ MV_XOR_V2_DMA_DESQ_ARATTR_OFF ; 
 int MV_XOR_V2_DMA_DESQ_ATTR_CACHEABLE ; 
 int MV_XOR_V2_DMA_DESQ_ATTR_CACHE_MASK ; 
 int MV_XOR_V2_DMA_DESQ_ATTR_OUTER_SHAREABLE ; 
 scalar_t__ MV_XOR_V2_DMA_DESQ_AWATTR_OFF ; 
 scalar_t__ MV_XOR_V2_DMA_DESQ_BAHR_OFF ; 
 scalar_t__ MV_XOR_V2_DMA_DESQ_BALR_OFF ; 
 scalar_t__ MV_XOR_V2_DMA_DESQ_SIZE_OFF ; 
 scalar_t__ MV_XOR_V2_DMA_DESQ_STOP_OFF ; 
 scalar_t__ MV_XOR_V2_GLOB_BW_CTRL ; 
 int MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_RD_SHIFT ; 
 int MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_RD_VAL ; 
 int MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_WR_SHIFT ; 
 int MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_WR_VAL ; 
 int MV_XOR_V2_GLOB_BW_CTRL_RD_BURST_LEN_SHIFT ; 
 int MV_XOR_V2_GLOB_BW_CTRL_RD_BURST_LEN_VAL ; 
 int MV_XOR_V2_GLOB_BW_CTRL_WR_BURST_LEN_SHIFT ; 
 int MV_XOR_V2_GLOB_BW_CTRL_WR_BURST_LEN_VAL ; 
 scalar_t__ MV_XOR_V2_GLOB_PAUSE ; 
 int MV_XOR_V2_GLOB_PAUSE_AXI_TIME_DIS_VAL ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mv_xor_v2_descq_init(struct mv_xor_v2_device *xor_dev)
{
	u32 reg;

	/* write the DESQ size to the DMA engine */
	writel(MV_XOR_V2_DESC_NUM,
	       xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_SIZE_OFF);

	/* write the DESQ address to the DMA enngine*/
	writel(lower_32_bits(xor_dev->hw_desq),
	       xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_BALR_OFF);
	writel(upper_32_bits(xor_dev->hw_desq),
	       xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_BAHR_OFF);

	/*
	 * This is a temporary solution, until we activate the
	 * SMMU. Set the attributes for reading & writing data buffers
	 * & descriptors to:
	 *
	 *  - OuterShareable - Snoops will be performed on CPU caches
	 *  - Enable cacheable - Bufferable, Modifiable, Other Allocate
	 *    and Allocate
	 */
	reg = readl(xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_ARATTR_OFF);
	reg &= ~MV_XOR_V2_DMA_DESQ_ATTR_CACHE_MASK;
	reg |= MV_XOR_V2_DMA_DESQ_ATTR_OUTER_SHAREABLE |
		MV_XOR_V2_DMA_DESQ_ATTR_CACHEABLE;
	writel(reg, xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_ARATTR_OFF);

	reg = readl(xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_AWATTR_OFF);
	reg &= ~MV_XOR_V2_DMA_DESQ_ATTR_CACHE_MASK;
	reg |= MV_XOR_V2_DMA_DESQ_ATTR_OUTER_SHAREABLE |
		MV_XOR_V2_DMA_DESQ_ATTR_CACHEABLE;
	writel(reg, xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_AWATTR_OFF);

	/* BW CTRL - set values to optimize the XOR performance:
	 *
	 *  - Set WrBurstLen & RdBurstLen - the unit will issue
	 *    maximum of 256B write/read transactions.
	 * -  Limit the number of outstanding write & read data
	 *    (OBB/IBB) requests to the maximal value.
	*/
	reg = ((MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_RD_VAL <<
		MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_RD_SHIFT) |
	       (MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_WR_VAL  <<
		MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_WR_SHIFT) |
	       (MV_XOR_V2_GLOB_BW_CTRL_RD_BURST_LEN_VAL <<
		MV_XOR_V2_GLOB_BW_CTRL_RD_BURST_LEN_SHIFT) |
	       (MV_XOR_V2_GLOB_BW_CTRL_WR_BURST_LEN_VAL <<
		MV_XOR_V2_GLOB_BW_CTRL_WR_BURST_LEN_SHIFT));
	writel(reg, xor_dev->glob_base + MV_XOR_V2_GLOB_BW_CTRL);

	/* Disable the AXI timer feature */
	reg = readl(xor_dev->glob_base + MV_XOR_V2_GLOB_PAUSE);
	reg |= MV_XOR_V2_GLOB_PAUSE_AXI_TIME_DIS_VAL;
	writel(reg, xor_dev->glob_base + MV_XOR_V2_GLOB_PAUSE);

	/* enable the DMA engine */
	writel(0, xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_STOP_OFF);

	return 0;
}