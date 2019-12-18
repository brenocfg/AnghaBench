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
struct regmap {int dummy; } ;

/* Variables and functions */
 int regmap_update_bits (struct regmap*,int,int,int) ; 

__attribute__((used)) static int intel_cht_wc_pmic_update_power(struct regmap *regmap, int reg,
		int bitmask, bool on)
{
	return regmap_update_bits(regmap, reg, bitmask, on ? 1 : 0);
}