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

__attribute__((used)) static u32 mmc_clk_delay(u32 val, u32 para, u32 off, u32 len)
{
	u32 i;

	for (i = 0; i < len; i++) {
		if (para % 2)
			val |= 1 << (off + i);
		else
			val &= ~(1 << (off + i));
		para = para >> 1;
	}

	return val;
}