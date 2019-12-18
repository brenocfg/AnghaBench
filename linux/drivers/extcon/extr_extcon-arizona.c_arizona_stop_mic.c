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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct arizona_extcon_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  micvdd; scalar_t__ micd_reva; struct arizona* arizona; } ;
struct arizona {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; struct snd_soc_dapm_context* dapm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_MICD_ENA ; 
 int /*<<< orphan*/  ARIZONA_MIC_DETECT_1 ; 
 char* arizona_extcon_get_micbias (struct arizona_extcon_info*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int regmap_update_bits_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int,int) ; 
 int regulator_allow_bypass (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int snd_soc_component_disable_pin (struct snd_soc_component*,char const*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static void arizona_stop_mic(struct arizona_extcon_info *info)
{
	struct arizona *arizona = info->arizona;
	const char *widget = arizona_extcon_get_micbias(info);
	struct snd_soc_dapm_context *dapm = arizona->dapm;
	struct snd_soc_component *component = snd_soc_dapm_to_component(dapm);
	bool change = false;
	int ret;

	ret = regmap_update_bits_check(arizona->regmap, ARIZONA_MIC_DETECT_1,
				       ARIZONA_MICD_ENA, 0,
				       &change);
	if (ret < 0)
		dev_err(arizona->dev, "Failed to disable micd: %d\n", ret);

	ret = snd_soc_component_disable_pin(component, widget);
	if (ret != 0)
		dev_warn(arizona->dev,
			 "Failed to disable %s: %d\n",
			 widget, ret);

	snd_soc_dapm_sync(dapm);

	if (info->micd_reva) {
		regmap_write(arizona->regmap, 0x80, 0x3);
		regmap_write(arizona->regmap, 0x294, 2);
		regmap_write(arizona->regmap, 0x80, 0x0);
	}

	ret = regulator_allow_bypass(info->micvdd, true);
	if (ret != 0) {
		dev_err(arizona->dev, "Failed to bypass MICVDD: %d\n",
			ret);
	}

	if (change) {
		regulator_disable(info->micvdd);
		pm_runtime_mark_last_busy(info->dev);
		pm_runtime_put_autosuspend(info->dev);
	}
}