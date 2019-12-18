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
struct mmp_tdma_filter_param {scalar_t__ chan_id; } ;
struct dma_chan {scalar_t__ chan_id; } ;

/* Variables and functions */

__attribute__((used)) static bool mmp_tdma_filter_fn(struct dma_chan *chan, void *fn_param)
{
	struct mmp_tdma_filter_param *param = fn_param;

	if (chan->chan_id != param->chan_id)
		return false;

	return true;
}