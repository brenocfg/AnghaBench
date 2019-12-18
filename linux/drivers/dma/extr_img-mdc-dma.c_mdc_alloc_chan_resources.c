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
struct mdc_chan {int /*<<< orphan*/  mdma; } ;
struct dma_chan {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* mdma2dev (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (struct device*) ; 
 struct mdc_chan* to_mdc_chan (struct dma_chan*) ; 

__attribute__((used)) static int mdc_alloc_chan_resources(struct dma_chan *chan)
{
	struct mdc_chan *mchan = to_mdc_chan(chan);
	struct device *dev = mdma2dev(mchan->mdma);

	return pm_runtime_get_sync(dev);
}