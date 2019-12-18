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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 struct clk_hw* clk_hw_register_fixed_factor (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static struct clk_hw *ast2600_calc_apll(const char *name, u32 val)
{
	unsigned int mult, div;

	if (val & BIT(20)) {
		/* Pass through mode */
		mult = div = 1;
	} else {
		/* F = 25Mhz * (2-od) * [(m + 2) / (n + 1)] */
		u32 m = (val >> 5) & 0x3f;
		u32 od = (val >> 4) & 0x1;
		u32 n = val & 0xf;

		mult = (2 - od) * (m + 2);
		div = n + 1;
	}
	return clk_hw_register_fixed_factor(NULL, name, "clkin", 0,
			mult, div);
}