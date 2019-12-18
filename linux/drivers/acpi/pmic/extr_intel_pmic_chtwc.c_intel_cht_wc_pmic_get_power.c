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
 int EIO ; 
 scalar_t__ regmap_read (struct regmap*,int,int*) ; 

__attribute__((used)) static int intel_cht_wc_pmic_get_power(struct regmap *regmap, int reg,
		int bit, u64 *value)
{
	int data;

	if (regmap_read(regmap, reg, &data))
		return -EIO;

	*value = (data & bit) ? 1 : 0;
	return 0;
}