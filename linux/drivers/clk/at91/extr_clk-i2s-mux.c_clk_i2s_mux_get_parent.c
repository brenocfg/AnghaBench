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
typedef  int u8 ;
typedef  int u32 ;
struct clk_i2s_mux {int bus_id; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SFR_I2SCLKSEL ; 
 int BIT (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct clk_i2s_mux* to_clk_i2s_mux (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_i2s_mux_get_parent(struct clk_hw *hw)
{
	struct clk_i2s_mux *mux = to_clk_i2s_mux(hw);
	u32 val;

	regmap_read(mux->regmap, AT91_SFR_I2SCLKSEL, &val);

	return (val & BIT(mux->bus_id)) >> mux->bus_id;
}