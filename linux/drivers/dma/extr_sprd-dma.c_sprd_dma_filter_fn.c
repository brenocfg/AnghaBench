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
typedef  int /*<<< orphan*/  u32 ;
struct sprd_dma_chn {int /*<<< orphan*/  dev_id; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct sprd_dma_chn* to_sprd_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static bool sprd_dma_filter_fn(struct dma_chan *chan, void *param)
{
	struct sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	u32 slave_id = *(u32 *)param;

	schan->dev_id = slave_id;
	return true;
}