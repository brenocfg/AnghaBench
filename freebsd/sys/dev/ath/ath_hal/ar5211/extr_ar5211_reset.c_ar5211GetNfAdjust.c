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
typedef  scalar_t__ uint16_t ;
struct ath_hal {int dummy; } ;
typedef  int int16_t ;
struct TYPE_3__ {scalar_t__ channel; } ;
typedef  TYPE_1__ HAL_CHANNEL_INTERNAL ;

/* Variables and functions */

int16_t
ar5211GetNfAdjust(struct ath_hal *ah, const HAL_CHANNEL_INTERNAL *c)
{
	static const struct {
		uint16_t freqLow;
		int16_t	  adjust;
	} adjust5111[] = {
		{ 5790,	11 },	/* NB: ordered high -> low */
		{ 5730, 10 },
		{ 5690,  9 },
		{ 5660,  8 },
		{ 5610,  7 },
		{ 5530,  5 },
		{ 5450,  4 },
		{ 5379,  2 },
		{ 5209,  0 },	/* XXX? bogus but doesn't matter */
		{    0,  1 },
	};
	int i;

	for (i = 0; c->channel <= adjust5111[i].freqLow; i++)
		;
	/* NB: placeholder for 5111's less severe requirement */
	return adjust5111[i].adjust / 3;
}