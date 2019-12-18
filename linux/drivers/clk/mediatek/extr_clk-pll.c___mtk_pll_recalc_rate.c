#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct mtk_clk_pll {TYPE_1__* data; } ;
struct TYPE_2__ {int pcwbits; int pcwibits; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int INTEGER_BITS ; 

__attribute__((used)) static unsigned long __mtk_pll_recalc_rate(struct mtk_clk_pll *pll, u32 fin,
		u32 pcw, int postdiv)
{
	int pcwbits = pll->data->pcwbits;
	int pcwfbits = 0;
	int ibits;
	u64 vco;
	u8 c = 0;

	/* The fractional part of the PLL divider. */
	ibits = pll->data->pcwibits ? pll->data->pcwibits : INTEGER_BITS;
	if (pcwbits > ibits)
		pcwfbits = pcwbits - ibits;

	vco = (u64)fin * pcw;

	if (pcwfbits && (vco & GENMASK(pcwfbits - 1, 0)))
		c = 1;

	vco >>= pcwfbits;

	if (c)
		vco++;

	return ((unsigned long)vco + postdiv - 1) / postdiv;
}