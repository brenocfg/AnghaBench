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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SAMPLE_AT_RESET_LOW ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_pclk_l2clk(int hclk, int core_index, int *pclk, int *l2clk)
{
	u32 cfg;

	/*
	 * Core #0 PCLK/L2CLK is configured by bits [13:8], core #1
	 * PCLK/L2CLK by bits [19:14].
	 */
	if (core_index == 0) {
		cfg = (readl(SAMPLE_AT_RESET_LOW) >> 8) & 0x3f;
	} else {
		cfg = (readl(SAMPLE_AT_RESET_LOW) >> 14) & 0x3f;
	}

	/*
	 * Bits [11:8] ([17:14] for core #1) configure the PCLK:HCLK
	 * ratio (1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6).
	 */
	*pclk = ((u64)hclk * (2 + (cfg & 0xf))) >> 1;

	/*
	 * Bits [13:12] ([19:18] for core #1) configure the PCLK:L2CLK
	 * ratio (1, 2, 3).
	 */
	*l2clk = *pclk / (((cfg >> 4) & 3) + 1);
}