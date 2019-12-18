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
struct regmap {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int regmap_update_bits (struct regmap*,int,int,int) ; 

__attribute__((used)) static int
intel_bxtwc_pmic_update_policy(struct regmap *regmap,
				int reg, int bit, int enable)
{
	u8 mask = BIT(bit), val = enable << bit;

	return regmap_update_bits(regmap, reg, mask, val);
}