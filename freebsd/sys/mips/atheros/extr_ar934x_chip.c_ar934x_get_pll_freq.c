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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int u_ar71xx_refclk ; 

__attribute__((used)) static uint32_t
ar934x_get_pll_freq(uint32_t ref, uint32_t ref_div, uint32_t nint,
    uint32_t nfrac, uint32_t frac, uint32_t out_div)
{
	uint64_t t;
	uint32_t ret;

	t = u_ar71xx_refclk;
	t *= nint;
	t = t / ref_div;
	ret = t;

	t = u_ar71xx_refclk;
	t *= nfrac;
	t = t / (ref_div * frac);
	ret += t;

	ret /= (1 << out_div);
	return (ret);
}