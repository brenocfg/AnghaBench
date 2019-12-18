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
struct dma_info {int nr_channels; struct dma_channel* channels; } ;
struct dma_channel {unsigned int vchan; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct dma_channel* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dma_info* get_dma_info (unsigned int) ; 
 scalar_t__ unlikely (int) ; 

struct dma_channel *get_dma_channel(unsigned int chan)
{
	struct dma_info *info = get_dma_info(chan);
	struct dma_channel *channel;
	int i;

	if (unlikely(!info))
		return ERR_PTR(-EINVAL);

	for (i = 0; i < info->nr_channels; i++) {
		channel = &info->channels[i];
		if (channel->vchan == chan)
			return channel;
	}

	return NULL;
}