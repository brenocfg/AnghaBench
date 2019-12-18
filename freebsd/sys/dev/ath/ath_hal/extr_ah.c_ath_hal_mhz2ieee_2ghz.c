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
struct ath_hal {int dummy; } ;

/* Variables and functions */

int
ath_hal_mhz2ieee_2ghz(struct ath_hal *ah, int freq)
{

	if (freq == 2484)
		return 14;
	if (freq < 2484)
		return ((int) freq - 2407) / 5;
	else
		return 15 + ((freq - 2512) / 20);
}