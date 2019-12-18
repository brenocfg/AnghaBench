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
typedef  int /*<<< orphan*/  u32 ;
struct clk_dyn_rcg {int /*<<< orphan*/  mux_sel_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_to_bank(struct clk_dyn_rcg *rcg, u32 bank)
{
	bank &= BIT(rcg->mux_sel_bit);
	return !!bank;
}