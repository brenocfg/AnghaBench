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
struct arizona_extcon_info {int hpdet_active; scalar_t__ mic; int /*<<< orphan*/  edev; int /*<<< orphan*/  dev; scalar_t__ hpdet_done; struct arizona* arizona; } ;
struct TYPE_2__ {int /*<<< orphan*/  hpdet_channel; } ;
struct arizona {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; TYPE_1__ pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_ACCDET_MODE_MASK ; 
 int /*<<< orphan*/  ARIZONA_ACCDET_MODE_MIC ; 
 int /*<<< orphan*/  ARIZONA_ACCESSORY_DETECT_MODE_1 ; 
 int /*<<< orphan*/  ARIZONA_HEADPHONE_DETECT_1 ; 
 int /*<<< orphan*/  ARIZONA_HP_POLL ; 
 int /*<<< orphan*/  EXTCON_JACK_HEADPHONE ; 
 int /*<<< orphan*/  arizona_extcon_hp_clamp (struct arizona_extcon_info*,int) ; 
 int /*<<< orphan*/  arizona_start_mic (struct arizona_extcon_info*) ; 
 int /*<<< orphan*/  arizona_stop_mic (struct arizona_extcon_info*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arizona_identify_headphone(struct arizona_extcon_info *info)
{
	struct arizona *arizona = info->arizona;
	int ret;

	if (info->hpdet_done)
		return;

	dev_dbg(arizona->dev, "Starting HPDET\n");

	/* Make sure we keep the device enabled during the measurement */
	pm_runtime_get(info->dev);

	info->hpdet_active = true;

	if (info->mic)
		arizona_stop_mic(info);

	arizona_extcon_hp_clamp(info, true);

	ret = regmap_update_bits(arizona->regmap,
				 ARIZONA_ACCESSORY_DETECT_MODE_1,
				 ARIZONA_ACCDET_MODE_MASK,
				 arizona->pdata.hpdet_channel);
	if (ret != 0) {
		dev_err(arizona->dev, "Failed to set HPDET mode: %d\n", ret);
		goto err;
	}

	ret = regmap_update_bits(arizona->regmap, ARIZONA_HEADPHONE_DETECT_1,
				 ARIZONA_HP_POLL, ARIZONA_HP_POLL);
	if (ret != 0) {
		dev_err(arizona->dev, "Can't start HPDETL measurement: %d\n",
			ret);
		goto err;
	}

	return;

err:
	regmap_update_bits(arizona->regmap, ARIZONA_ACCESSORY_DETECT_MODE_1,
			   ARIZONA_ACCDET_MODE_MASK, ARIZONA_ACCDET_MODE_MIC);

	/* Just report headphone */
	ret = extcon_set_state_sync(info->edev, EXTCON_JACK_HEADPHONE, true);
	if (ret != 0)
		dev_err(arizona->dev, "Failed to report headphone: %d\n", ret);

	if (info->mic)
		arizona_start_mic(info);

	info->hpdet_active = false;
}