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
typedef  size_t u8 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 size_t WHISKEY_COVE_ADC_CURSRC (size_t) ; 
 size_t WHISKEY_COVE_ADC_HIGH_BIT (size_t) ; 
 scalar_t__ regmap_read (struct regmap*,int,unsigned int*) ; 

__attribute__((used)) static int intel_bxtwc_pmic_get_raw_temp(struct regmap *regmap, int reg)
{
	unsigned int val, adc_val, reg_val;
	u8 temp_l, temp_h, cursrc;
	unsigned long rlsb;
	static const unsigned long rlsb_array[] = {
		0, 260420, 130210, 65100, 32550, 16280,
		8140, 4070, 2030, 0, 260420, 130210 };

	if (regmap_read(regmap, reg, &val))
		return -EIO;
	temp_l = (u8) val;

	if (regmap_read(regmap, (reg - 1), &val))
		return -EIO;
	temp_h = (u8) val;

	reg_val = temp_l | WHISKEY_COVE_ADC_HIGH_BIT(temp_h);
	cursrc = WHISKEY_COVE_ADC_CURSRC(temp_h);
	rlsb = rlsb_array[cursrc];
	adc_val = reg_val * rlsb / 1000;

	return adc_val;
}