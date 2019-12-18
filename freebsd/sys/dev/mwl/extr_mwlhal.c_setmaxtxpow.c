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
struct mwl_hal_channel {scalar_t__ maxTxPow; scalar_t__* targetPowers; } ;

/* Variables and functions */

__attribute__((used)) static void
setmaxtxpow(struct mwl_hal_channel *hc, int i, int maxix)
{
	hc->maxTxPow = hc->targetPowers[i];
	for (i++; i < maxix; i++)
		if (hc->targetPowers[i] > hc->maxTxPow)
			hc->maxTxPow = hc->targetPowers[i];
}