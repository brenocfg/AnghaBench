#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct arizona_extcon_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  micvdd; scalar_t__ detecting; scalar_t__ micd_reva; struct arizona* arizona; } ;
struct TYPE_2__ {scalar_t__ micd_software_compare; } ;
struct arizona {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; TYPE_1__ pdata; } ;

/* Variables and functions */
 unsigned int ARIZONA_ACCDET_MODE_ADC ; 
 int /*<<< orphan*/  ARIZONA_ACCDET_MODE_MASK ; 
 unsigned int ARIZONA_ACCDET_MODE_MIC ; 
 int /*<<< orphan*/  ARIZONA_ACCESSORY_DETECT_MODE_1 ; 
 int /*<<< orphan*/  ARIZONA_MICD_ENA ; 
 int /*<<< orphan*/  ARIZONA_MIC_DETECT_1 ; 
 int /*<<< orphan*/  arizona_extcon_pulse_micbias (struct arizona_extcon_info*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int regmap_update_bits_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int regulator_allow_bypass (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arizona_start_mic(struct arizona_extcon_info *info)
{
	struct arizona *arizona = info->arizona;
	bool change;
	int ret;
	unsigned int mode;

	/* Microphone detection can't use idle mode */
	pm_runtime_get(info->dev);

	if (info->detecting) {
		ret = regulator_allow_bypass(info->micvdd, false);
		if (ret != 0) {
			dev_err(arizona->dev,
				"Failed to regulate MICVDD: %d\n",
				ret);
		}
	}

	ret = regulator_enable(info->micvdd);
	if (ret != 0) {
		dev_err(arizona->dev, "Failed to enable MICVDD: %d\n",
			ret);
	}

	if (info->micd_reva) {
		regmap_write(arizona->regmap, 0x80, 0x3);
		regmap_write(arizona->regmap, 0x294, 0);
		regmap_write(arizona->regmap, 0x80, 0x0);
	}

	if (info->detecting && arizona->pdata.micd_software_compare)
		mode = ARIZONA_ACCDET_MODE_ADC;
	else
		mode = ARIZONA_ACCDET_MODE_MIC;

	regmap_update_bits(arizona->regmap,
			   ARIZONA_ACCESSORY_DETECT_MODE_1,
			   ARIZONA_ACCDET_MODE_MASK, mode);

	arizona_extcon_pulse_micbias(info);

	ret = regmap_update_bits_check(arizona->regmap, ARIZONA_MIC_DETECT_1,
				       ARIZONA_MICD_ENA, ARIZONA_MICD_ENA,
				       &change);
	if (ret < 0) {
		dev_err(arizona->dev, "Failed to enable micd: %d\n", ret);
	} else if (!change) {
		regulator_disable(info->micvdd);
		pm_runtime_put_autosuspend(info->dev);
	}
}