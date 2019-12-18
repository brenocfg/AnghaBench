#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mwl_hal_channel {int ieee; } ;
struct TYPE_3__ {int nchannels; struct mwl_hal_channel* channels; } ;
typedef  TYPE_1__ MWL_HAL_CHANNELINFO ;

/* Variables and functions */

__attribute__((used)) static const struct mwl_hal_channel *
findhalchannel(const MWL_HAL_CHANNELINFO *ci, int ieee)
{
	int i;

	for (i = 0; i < ci->nchannels; i++) {
		const struct mwl_hal_channel *hc = &ci->channels[i];
		if (hc->ieee == ieee)
			return hc;
	}
	return NULL;
}