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
typedef  int /*<<< orphan*/  uint8_t ;
struct mwl_hal_channel {int ieee; int /*<<< orphan*/  targetPowers; void* freq; } ;
struct TYPE_3__ {int nchannels; void* freqHigh; void* freqLow; struct mwl_hal_channel* channels; } ;
typedef  TYPE_1__ MWL_HAL_CHANNELINFO ;

/* Variables and functions */
 void* ieee2mhz (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  setmaxtxpow (struct mwl_hal_channel*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
get2Ghz(MWL_HAL_CHANNELINFO *ci, const uint8_t table[], int len)
{
	int i, j;

	j = 0;
	for (i = 0; i < len; i += 4) {
		struct mwl_hal_channel *hc = &ci->channels[j];
		hc->ieee = 1+j;
		hc->freq = ieee2mhz(1+j);
		memcpy(hc->targetPowers, &table[i], 4);
		setmaxtxpow(hc, 0, 4);
		j++;
	}
	ci->nchannels = j;
	ci->freqLow = ieee2mhz(1);
	ci->freqHigh = ieee2mhz(j);
}