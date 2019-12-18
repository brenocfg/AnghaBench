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
struct dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct dma_chan* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dma_chan* __dma_request_channel (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_device_list ; 
 int /*<<< orphan*/  dma_list_mutex ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct dma_chan *dma_request_chan_by_mask(const dma_cap_mask_t *mask)
{
	struct dma_chan *chan;

	if (!mask)
		return ERR_PTR(-ENODEV);

	chan = __dma_request_channel(mask, NULL, NULL, NULL);
	if (!chan) {
		mutex_lock(&dma_list_mutex);
		if (list_empty(&dma_device_list))
			chan = ERR_PTR(-EPROBE_DEFER);
		else
			chan = ERR_PTR(-ENODEV);
		mutex_unlock(&dma_list_mutex);
	}

	return chan;
}