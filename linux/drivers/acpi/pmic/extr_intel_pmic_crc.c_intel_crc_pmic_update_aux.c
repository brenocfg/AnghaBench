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
 int EIO ; 
 scalar_t__ regmap_update_bits (struct regmap*,int,int,int) ; 
 scalar_t__ regmap_write (struct regmap*,int,int) ; 

__attribute__((used)) static int intel_crc_pmic_update_aux(struct regmap *regmap, int reg, int raw)
{
	return regmap_write(regmap, reg, raw) ||
		regmap_update_bits(regmap, reg - 1, 0x3, raw >> 8) ? -EIO : 0;
}