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
struct sdma_engine {int /*<<< orphan*/ * channel; int /*<<< orphan*/  bd0_phys; TYPE_1__* channel_control; int /*<<< orphan*/  bd0; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  current_bd_ptr; int /*<<< orphan*/  base_bd_ptr; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  MXC_SDMA_DEFAULT_PRIORITY ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_set_channel_priority (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdma_request_channel0(struct sdma_engine *sdma)
{
	int ret = -EBUSY;

	sdma->bd0 = dma_alloc_coherent(sdma->dev, PAGE_SIZE, &sdma->bd0_phys,
					GFP_NOWAIT);
	if (!sdma->bd0) {
		ret = -ENOMEM;
		goto out;
	}

	sdma->channel_control[0].base_bd_ptr = sdma->bd0_phys;
	sdma->channel_control[0].current_bd_ptr = sdma->bd0_phys;

	sdma_set_channel_priority(&sdma->channel[0], MXC_SDMA_DEFAULT_PRIORITY);
	return 0;
out:

	return ret;
}