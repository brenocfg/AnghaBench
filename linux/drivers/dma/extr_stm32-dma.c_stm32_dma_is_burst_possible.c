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

__attribute__((used)) static bool stm32_dma_is_burst_possible(u32 buf_len, u32 threshold)
{
	/*
	 * Buffer or period length has to be aligned on FIFO depth.
	 * Otherwise bytes may be stuck within FIFO at buffer or period
	 * length.
	 */
	return ((buf_len % ((threshold + 1) * 4)) == 0);
}