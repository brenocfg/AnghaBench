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
 int PMIC_A0LOCK_REG ; 
 scalar_t__ regmap_read (struct regmap*,int,int*) ; 
 scalar_t__ regmap_update_bits (struct regmap*,int,int,int) ; 
 scalar_t__ regmap_write (struct regmap*,int,int) ; 

__attribute__((used)) static int intel_crc_pmic_update_policy(struct regmap *regmap,
					int reg, int bit, int enable)
{
	int alert0;

	/* Update to policy enable bit requires unlocking a0lock */
	if (regmap_read(regmap, PMIC_A0LOCK_REG, &alert0))
		return -EIO;

	if (regmap_update_bits(regmap, PMIC_A0LOCK_REG, 0x01, 0))
		return -EIO;

	if (regmap_update_bits(regmap, reg, 0x80, enable << 7))
		return -EIO;

	/* restore alert0 */
	if (regmap_write(regmap, PMIC_A0LOCK_REG, alert0))
		return -EIO;

	return 0;
}