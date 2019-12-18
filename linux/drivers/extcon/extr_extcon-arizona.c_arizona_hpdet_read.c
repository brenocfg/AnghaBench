#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct arizona_extcon_info {int hpdet_ip_version; struct arizona* arizona; } ;
struct arizona {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {unsigned int threshold; unsigned int factor_b; unsigned int max; unsigned int min; int /*<<< orphan*/  factor_a; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_HEADPHONE_DETECT_1 ; 
 int /*<<< orphan*/  ARIZONA_HEADPHONE_DETECT_2 ; 
 unsigned int ARIZONA_HPDET_B_RANGE_MAX ; 
 int ARIZONA_HPDET_MAX ; 
 int /*<<< orphan*/  ARIZONA_HP_DACVAL ; 
 unsigned int ARIZONA_HP_DONE ; 
 unsigned int ARIZONA_HP_DONE_B ; 
 unsigned int ARIZONA_HP_IMPEDANCE_RANGE_MASK ; 
 unsigned int ARIZONA_HP_IMPEDANCE_RANGE_SHIFT ; 
 unsigned int ARIZONA_HP_LVL_B_MASK ; 
 unsigned int ARIZONA_HP_LVL_MASK ; 
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int EAGAIN ; 
 int EINVAL ; 
 TYPE_1__* arizona_hpdet_b_ranges ; 
 TYPE_1__* arizona_hpdet_c_ranges ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int arizona_hpdet_read(struct arizona_extcon_info *info)
{
	struct arizona *arizona = info->arizona;
	unsigned int val, range;
	int ret;

	ret = regmap_read(arizona->regmap, ARIZONA_HEADPHONE_DETECT_2, &val);
	if (ret != 0) {
		dev_err(arizona->dev, "Failed to read HPDET status: %d\n",
			ret);
		return ret;
	}

	switch (info->hpdet_ip_version) {
	case 0:
		if (!(val & ARIZONA_HP_DONE)) {
			dev_err(arizona->dev, "HPDET did not complete: %x\n",
				val);
			return -EAGAIN;
		}

		val &= ARIZONA_HP_LVL_MASK;
		break;

	case 1:
		if (!(val & ARIZONA_HP_DONE_B)) {
			dev_err(arizona->dev, "HPDET did not complete: %x\n",
				val);
			return -EAGAIN;
		}

		ret = regmap_read(arizona->regmap, ARIZONA_HP_DACVAL, &val);
		if (ret != 0) {
			dev_err(arizona->dev, "Failed to read HP value: %d\n",
				ret);
			return -EAGAIN;
		}

		regmap_read(arizona->regmap, ARIZONA_HEADPHONE_DETECT_1,
			    &range);
		range = (range & ARIZONA_HP_IMPEDANCE_RANGE_MASK)
			   >> ARIZONA_HP_IMPEDANCE_RANGE_SHIFT;

		if (range < ARRAY_SIZE(arizona_hpdet_b_ranges) - 1 &&
		    (val < arizona_hpdet_b_ranges[range].threshold ||
		     val >= ARIZONA_HPDET_B_RANGE_MAX)) {
			range++;
			dev_dbg(arizona->dev, "Moving to HPDET range %d\n",
				range);
			regmap_update_bits(arizona->regmap,
					   ARIZONA_HEADPHONE_DETECT_1,
					   ARIZONA_HP_IMPEDANCE_RANGE_MASK,
					   range <<
					   ARIZONA_HP_IMPEDANCE_RANGE_SHIFT);
			return -EAGAIN;
		}

		/* If we go out of range report top of range */
		if (val < arizona_hpdet_b_ranges[range].threshold ||
		    val >= ARIZONA_HPDET_B_RANGE_MAX) {
			dev_dbg(arizona->dev, "Measurement out of range\n");
			return ARIZONA_HPDET_MAX;
		}

		dev_dbg(arizona->dev, "HPDET read %d in range %d\n",
			val, range);

		val = arizona_hpdet_b_ranges[range].factor_b
			/ ((val * 100) -
			   arizona_hpdet_b_ranges[range].factor_a);
		break;

	case 2:
		if (!(val & ARIZONA_HP_DONE_B)) {
			dev_err(arizona->dev, "HPDET did not complete: %x\n",
				val);
			return -EAGAIN;
		}

		val &= ARIZONA_HP_LVL_B_MASK;
		/* Convert to ohms, the value is in 0.5 ohm increments */
		val /= 2;

		regmap_read(arizona->regmap, ARIZONA_HEADPHONE_DETECT_1,
			    &range);
		range = (range & ARIZONA_HP_IMPEDANCE_RANGE_MASK)
			   >> ARIZONA_HP_IMPEDANCE_RANGE_SHIFT;

		/* Skip up a range, or report? */
		if (range < ARRAY_SIZE(arizona_hpdet_c_ranges) - 1 &&
		    (val >= arizona_hpdet_c_ranges[range].max)) {
			range++;
			dev_dbg(arizona->dev, "Moving to HPDET range %d-%d\n",
				arizona_hpdet_c_ranges[range].min,
				arizona_hpdet_c_ranges[range].max);
			regmap_update_bits(arizona->regmap,
					   ARIZONA_HEADPHONE_DETECT_1,
					   ARIZONA_HP_IMPEDANCE_RANGE_MASK,
					   range <<
					   ARIZONA_HP_IMPEDANCE_RANGE_SHIFT);
			return -EAGAIN;
		}

		if (range && (val < arizona_hpdet_c_ranges[range].min)) {
			dev_dbg(arizona->dev, "Reporting range boundary %d\n",
				arizona_hpdet_c_ranges[range].min);
			val = arizona_hpdet_c_ranges[range].min;
		}
		break;

	default:
		dev_warn(arizona->dev, "Unknown HPDET IP revision %d\n",
			 info->hpdet_ip_version);
		return -EINVAL;
	}

	dev_dbg(arizona->dev, "HP impedance %d ohms\n", val);
	return val;
}