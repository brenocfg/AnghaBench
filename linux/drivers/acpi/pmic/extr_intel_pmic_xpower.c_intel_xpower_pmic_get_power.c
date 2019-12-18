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
struct regmap {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EIO ; 
 int GPI1_LDO_MASK ; 
 int GPI1_LDO_ON ; 
 int XPOWER_GPI1_CTRL ; 
 scalar_t__ regmap_read (struct regmap*,int,int*) ; 

__attribute__((used)) static int intel_xpower_pmic_get_power(struct regmap *regmap, int reg,
				       int bit, u64 *value)
{
	int data;

	if (regmap_read(regmap, reg, &data))
		return -EIO;

	/* GPIO1 LDO regulator needs special handling */
	if (reg == XPOWER_GPI1_CTRL)
		*value = ((data & GPI1_LDO_MASK) == GPI1_LDO_ON);
	else
		*value = (data & BIT(bit)) ? 1 : 0;

	return 0;
}