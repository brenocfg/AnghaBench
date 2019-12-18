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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct arizona_extcon_info {int /*<<< orphan*/  hpdet_work; scalar_t__ micd_clamp; int /*<<< orphan*/  micd_pol_gpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  micvdd; struct arizona* arizona; } ;
struct arizona {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ARIZONA_IRQ_HPDET ; 
 int ARIZONA_IRQ_JD_FALL ; 
 int ARIZONA_IRQ_JD_RISE ; 
 int ARIZONA_IRQ_MICDET ; 
 int ARIZONA_IRQ_MICD_CLAMP_FALL ; 
 int ARIZONA_IRQ_MICD_CLAMP_RISE ; 
 int /*<<< orphan*/  ARIZONA_JACK_DETECT_ANALOGUE ; 
 int /*<<< orphan*/  ARIZONA_JD1_ENA ; 
 int /*<<< orphan*/  ARIZONA_MICD_CLAMP_CONTROL ; 
 int /*<<< orphan*/  ARIZONA_MICD_CLAMP_MODE_MASK ; 
 int /*<<< orphan*/  ARIZONA_MICD_ENA ; 
 int /*<<< orphan*/  ARIZONA_MIC_DETECT_1 ; 
 int /*<<< orphan*/  arizona_clk32k_disable (struct arizona*) ; 
 int /*<<< orphan*/  arizona_free_irq (struct arizona*,int,struct arizona_extcon_info*) ; 
 int /*<<< orphan*/  arizona_set_irq_wake (struct arizona*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpiod_put (int /*<<< orphan*/ ) ; 
 struct arizona_extcon_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_update_bits_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arizona_extcon_remove(struct platform_device *pdev)
{
	struct arizona_extcon_info *info = platform_get_drvdata(pdev);
	struct arizona *arizona = info->arizona;
	int jack_irq_rise, jack_irq_fall;
	bool change;
	int ret;

	ret = regmap_update_bits_check(arizona->regmap, ARIZONA_MIC_DETECT_1,
				       ARIZONA_MICD_ENA, 0,
				       &change);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to disable micd on remove: %d\n",
			ret);
	} else if (change) {
		regulator_disable(info->micvdd);
		pm_runtime_put(info->dev);
	}

	gpiod_put(info->micd_pol_gpio);

	pm_runtime_disable(&pdev->dev);

	regmap_update_bits(arizona->regmap,
			   ARIZONA_MICD_CLAMP_CONTROL,
			   ARIZONA_MICD_CLAMP_MODE_MASK, 0);

	if (info->micd_clamp) {
		jack_irq_rise = ARIZONA_IRQ_MICD_CLAMP_RISE;
		jack_irq_fall = ARIZONA_IRQ_MICD_CLAMP_FALL;
	} else {
		jack_irq_rise = ARIZONA_IRQ_JD_RISE;
		jack_irq_fall = ARIZONA_IRQ_JD_FALL;
	}

	arizona_set_irq_wake(arizona, jack_irq_rise, 0);
	arizona_set_irq_wake(arizona, jack_irq_fall, 0);
	arizona_free_irq(arizona, ARIZONA_IRQ_HPDET, info);
	arizona_free_irq(arizona, ARIZONA_IRQ_MICDET, info);
	arizona_free_irq(arizona, jack_irq_rise, info);
	arizona_free_irq(arizona, jack_irq_fall, info);
	cancel_delayed_work_sync(&info->hpdet_work);
	regmap_update_bits(arizona->regmap, ARIZONA_JACK_DETECT_ANALOGUE,
			   ARIZONA_JD1_ENA, 0);
	arizona_clk32k_disable(arizona);

	return 0;
}