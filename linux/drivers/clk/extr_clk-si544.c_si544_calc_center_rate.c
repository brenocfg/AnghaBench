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
struct clk_si544_muldiv {int hs_div; scalar_t__ fb_div_int; scalar_t__ fb_div_frac; int /*<<< orphan*/  ls_div_bits; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int FXO ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static unsigned long si544_calc_center_rate(
		const struct clk_si544_muldiv *settings)
{
	u32 d = settings->hs_div * BIT(settings->ls_div_bits);
	u64 vco;

	/* Calculate VCO from the fractional part */
	vco = (u64)settings->fb_div_frac * FXO;
	vco += (FXO / 2);
	vco >>= 32;

	/* Add the integer part of the VCO frequency */
	vco += (u64)settings->fb_div_int * FXO;

	/* Apply divider to obtain the generated frequency */
	do_div(vco, d);

	return vco;
}