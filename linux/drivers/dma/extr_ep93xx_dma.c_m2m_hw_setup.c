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
typedef  int u32 ;
struct ep93xx_dma_data {int port; int /*<<< orphan*/  direction; } ;
struct TYPE_2__ {struct ep93xx_dma_data* private; } ;
struct ep93xx_dma_chan {scalar_t__ regs; TYPE_1__ chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int EINVAL ; 
#define  EP93XX_DMA_IDE 129 
#define  EP93XX_DMA_SSP 128 
 scalar_t__ M2M_CONTROL ; 
 int M2M_CONTROL_DAH ; 
 int M2M_CONTROL_NO_HDSK ; 
 int M2M_CONTROL_PWSC_SHIFT ; 
 int M2M_CONTROL_PW_16 ; 
 int M2M_CONTROL_RSS_IDE ; 
 int M2M_CONTROL_RSS_SSPRX ; 
 int M2M_CONTROL_RSS_SSPTX ; 
 int M2M_CONTROL_SAH ; 
 int M2M_CONTROL_TM_RX ; 
 int M2M_CONTROL_TM_TX ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int m2m_hw_setup(struct ep93xx_dma_chan *edmac)
{
	const struct ep93xx_dma_data *data = edmac->chan.private;
	u32 control = 0;

	if (!data) {
		/* This is memcpy channel, nothing to configure */
		writel(control, edmac->regs + M2M_CONTROL);
		return 0;
	}

	switch (data->port) {
	case EP93XX_DMA_SSP:
		/*
		 * This was found via experimenting - anything less than 5
		 * causes the channel to perform only a partial transfer which
		 * leads to problems since we don't get DONE interrupt then.
		 */
		control = (5 << M2M_CONTROL_PWSC_SHIFT);
		control |= M2M_CONTROL_NO_HDSK;

		if (data->direction == DMA_MEM_TO_DEV) {
			control |= M2M_CONTROL_DAH;
			control |= M2M_CONTROL_TM_TX;
			control |= M2M_CONTROL_RSS_SSPTX;
		} else {
			control |= M2M_CONTROL_SAH;
			control |= M2M_CONTROL_TM_RX;
			control |= M2M_CONTROL_RSS_SSPRX;
		}
		break;

	case EP93XX_DMA_IDE:
		/*
		 * This IDE part is totally untested. Values below are taken
		 * from the EP93xx Users's Guide and might not be correct.
		 */
		if (data->direction == DMA_MEM_TO_DEV) {
			/* Worst case from the UG */
			control = (3 << M2M_CONTROL_PWSC_SHIFT);
			control |= M2M_CONTROL_DAH;
			control |= M2M_CONTROL_TM_TX;
		} else {
			control = (2 << M2M_CONTROL_PWSC_SHIFT);
			control |= M2M_CONTROL_SAH;
			control |= M2M_CONTROL_TM_RX;
		}

		control |= M2M_CONTROL_NO_HDSK;
		control |= M2M_CONTROL_RSS_IDE;
		control |= M2M_CONTROL_PW_16;
		break;

	default:
		return -EINVAL;
	}

	writel(control, edmac->regs + M2M_CONTROL);
	return 0;
}