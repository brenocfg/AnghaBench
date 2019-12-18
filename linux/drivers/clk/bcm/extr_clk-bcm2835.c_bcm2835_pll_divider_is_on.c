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
struct clk_hw {int dummy; } ;
struct bcm2835_pll_divider_data {int /*<<< orphan*/  a2w_reg; } ;
struct bcm2835_pll_divider {struct bcm2835_pll_divider_data* data; struct bcm2835_cprman* cprman; } ;
struct bcm2835_cprman {int dummy; } ;

/* Variables and functions */
 int A2W_PLL_CHANNEL_DISABLE ; 
 struct bcm2835_pll_divider* bcm2835_pll_divider_from_hw (struct clk_hw*) ; 
 int cprman_read (struct bcm2835_cprman*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2835_pll_divider_is_on(struct clk_hw *hw)
{
	struct bcm2835_pll_divider *divider = bcm2835_pll_divider_from_hw(hw);
	struct bcm2835_cprman *cprman = divider->cprman;
	const struct bcm2835_pll_divider_data *data = divider->data;

	return !(cprman_read(cprman, data->a2w_reg) & A2W_PLL_CHANNEL_DISABLE);
}