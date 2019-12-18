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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct sprd_dma_dev {TYPE_2__ dma_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct sprd_dma_chn {scalar_t__ chn_base; TYPE_1__ vc; } ;

/* Variables and functions */
 scalar_t__ SPRD_DMA_CHN_PAUSE ; 
 scalar_t__ SPRD_DMA_PAUSE_CNT ; 
 int /*<<< orphan*/  SPRD_DMA_PAUSE_EN ; 
 scalar_t__ SPRD_DMA_PAUSE_STS ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  sprd_dma_chn_update (struct sprd_dma_chn*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sprd_dma_dev* to_sprd_dma_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sprd_dma_pause_resume(struct sprd_dma_chn *schan, bool enable)
{
	struct sprd_dma_dev *sdev = to_sprd_dma_dev(&schan->vc.chan);
	u32 pause, timeout = SPRD_DMA_PAUSE_CNT;

	if (enable) {
		sprd_dma_chn_update(schan, SPRD_DMA_CHN_PAUSE,
				    SPRD_DMA_PAUSE_EN, SPRD_DMA_PAUSE_EN);

		do {
			pause = readl(schan->chn_base + SPRD_DMA_CHN_PAUSE);
			if (pause & SPRD_DMA_PAUSE_STS)
				break;

			cpu_relax();
		} while (--timeout > 0);

		if (!timeout)
			dev_warn(sdev->dma_dev.dev,
				 "pause dma controller timeout\n");
	} else {
		sprd_dma_chn_update(schan, SPRD_DMA_CHN_PAUSE,
				    SPRD_DMA_PAUSE_EN, 0);
	}
}