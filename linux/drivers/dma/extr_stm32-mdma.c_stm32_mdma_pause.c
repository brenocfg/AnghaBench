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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct stm32_mdma_chan {TYPE_1__ vchan; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (struct stm32_mdma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stm32_mdma_disable_chan (struct stm32_mdma_chan*) ; 
 struct stm32_mdma_chan* to_stm32_mdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int stm32_mdma_pause(struct dma_chan *c)
{
	struct stm32_mdma_chan *chan = to_stm32_mdma_chan(c);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&chan->vchan.lock, flags);
	ret = stm32_mdma_disable_chan(chan);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	if (!ret)
		dev_dbg(chan2dev(chan), "vchan %pK: pause\n", &chan->vchan);

	return ret;
}