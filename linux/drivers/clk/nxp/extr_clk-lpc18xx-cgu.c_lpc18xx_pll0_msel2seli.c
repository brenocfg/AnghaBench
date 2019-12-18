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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 lpc18xx_pll0_msel2seli(u32 msel)
{
	u32 tmp;

	if (msel > 16384) return 1;
	if (msel >  8192) return 2;
	if (msel >  2048) return 4;
	if (msel >=  501) return 8;
	if (msel >=   60) {
		tmp = 1024 / (msel + 9);
		return ((1024 == (tmp * (msel + 9))) == 0) ? tmp * 4 : (tmp + 1) * 4;
	}

	return (msel & 0x3c) + 4;
}