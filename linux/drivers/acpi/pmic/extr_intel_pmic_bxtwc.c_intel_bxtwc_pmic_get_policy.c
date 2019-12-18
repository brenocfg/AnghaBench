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
typedef  unsigned int u8 ;
typedef  unsigned int u64 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int EIO ; 
 scalar_t__ regmap_read (struct regmap*,int,unsigned int*) ; 

__attribute__((used)) static int
intel_bxtwc_pmic_get_policy(struct regmap *regmap, int reg, int bit, u64 *value)
{
	u8 mask = BIT(bit);
	unsigned int val;

	if (regmap_read(regmap, reg, &val))
		return -EIO;

	*value = (val & mask) >> bit;
	return 0;
}