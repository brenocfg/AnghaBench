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
struct max77843_muic_info {int /*<<< orphan*/  dev; struct max77693_dev* max77843; } ;
struct max77693_dev {int /*<<< orphan*/  regmap_muic; } ;
typedef  enum max77843_muic_adc_debounce_time { ____Placeholder_max77843_muic_adc_debounce_time } max77843_muic_adc_debounce_time ;

/* Variables and functions */
 int EINVAL ; 
#define  MAX77843_DEBOUNCE_TIME_10MS 131 
#define  MAX77843_DEBOUNCE_TIME_25MS 130 
#define  MAX77843_DEBOUNCE_TIME_38_62MS 129 
#define  MAX77843_DEBOUNCE_TIME_5MS 128 
 int /*<<< orphan*/  MAX77843_MUIC_CONTROL4_ADCDBSET_MASK ; 
 int MAX77843_MUIC_CONTROL4_ADCDBSET_SHIFT ; 
 int /*<<< orphan*/  MAX77843_MUIC_REG_CONTROL4 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max77843_muic_set_debounce_time(struct max77843_muic_info *info,
		enum max77843_muic_adc_debounce_time time)
{
	struct max77693_dev *max77843 = info->max77843;
	int ret;

	switch (time) {
	case MAX77843_DEBOUNCE_TIME_5MS:
	case MAX77843_DEBOUNCE_TIME_10MS:
	case MAX77843_DEBOUNCE_TIME_25MS:
	case MAX77843_DEBOUNCE_TIME_38_62MS:
		ret = regmap_update_bits(max77843->regmap_muic,
				MAX77843_MUIC_REG_CONTROL4,
				MAX77843_MUIC_CONTROL4_ADCDBSET_MASK,
				time << MAX77843_MUIC_CONTROL4_ADCDBSET_SHIFT);
		if (ret < 0) {
			dev_err(info->dev, "Cannot write MUIC regmap\n");
			return ret;
		}
		break;
	default:
		dev_err(info->dev, "Invalid ADC debounce time\n");
		return -EINVAL;
	}

	return 0;
}