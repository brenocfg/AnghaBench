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
struct jz4780_dma_dev {TYPE_1__* soc_data; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 unsigned int JZ_DMA_REG_DCKE ; 
 unsigned int JZ_DMA_REG_DCKES ; 
 int JZ_SOC_DATA_NO_DCKES_DCKEC ; 
 int JZ_SOC_DATA_PER_CHAN_PM ; 
 int /*<<< orphan*/  jz4780_dma_ctrl_writel (struct jz4780_dma_dev*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void jz4780_dma_chan_enable(struct jz4780_dma_dev *jzdma,
	unsigned int chn)
{
	if (jzdma->soc_data->flags & JZ_SOC_DATA_PER_CHAN_PM) {
		unsigned int reg;

		if (jzdma->soc_data->flags & JZ_SOC_DATA_NO_DCKES_DCKEC)
			reg = JZ_DMA_REG_DCKE;
		else
			reg = JZ_DMA_REG_DCKES;

		jz4780_dma_ctrl_writel(jzdma, reg, BIT(chn));
	}
}