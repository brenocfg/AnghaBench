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
struct clk_zx_audio_divider {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long audio_calc_rate(struct clk_zx_audio_divider *audio_div,
				     u32 reg_frac, u32 reg_int,
				     unsigned long parent_rate)
{
	unsigned long rate, m, n;

	m = reg_frac & 0xffff;
	n = (reg_frac >> 16) & 0xffff;

	m = (reg_int & 0xffff) * n + m;
	rate = (parent_rate * n) / m;

	return rate;
}