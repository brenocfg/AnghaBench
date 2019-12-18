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
struct arizona_extcon_info {int hpdet_active; int hpdet_done; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; scalar_t__ mic; int /*<<< orphan*/  edev; struct arizona* arizona; } ;
struct TYPE_2__ {int hpdet_id_gpio; } ;
struct arizona {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; TYPE_1__ pdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ARIZONA_ACCDET_MODE_MASK ; 
 int /*<<< orphan*/  ARIZONA_ACCDET_MODE_MIC ; 
 int /*<<< orphan*/  ARIZONA_ACCESSORY_DETECT_MODE_1 ; 
 int /*<<< orphan*/  ARIZONA_HEADPHONE_DETECT_1 ; 
 int ARIZONA_HP_IMPEDANCE_RANGE_MASK ; 
 int ARIZONA_HP_POLL ; 
 int EAGAIN ; 
 unsigned int EXTCON_JACK_HEADPHONE ; 
 unsigned int EXTCON_JACK_LINE_OUT ; 
 int /*<<< orphan*/  EXTCON_MECHANICAL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  arizona_extcon_hp_clamp (struct arizona_extcon_info*,int) ; 
 int arizona_hpdet_do_id (struct arizona_extcon_info*,int*,int*) ; 
 int arizona_hpdet_read (struct arizona_extcon_info*) ; 
 int /*<<< orphan*/  arizona_start_mic (struct arizona_extcon_info*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int extcon_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int extcon_set_state_sync (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t arizona_hpdet_irq(int irq, void *data)
{
	struct arizona_extcon_info *info = data;
	struct arizona *arizona = info->arizona;
	int id_gpio = arizona->pdata.hpdet_id_gpio;
	unsigned int report = EXTCON_JACK_HEADPHONE;
	int ret, reading;
	bool mic = false;

	mutex_lock(&info->lock);

	/* If we got a spurious IRQ for some reason then ignore it */
	if (!info->hpdet_active) {
		dev_warn(arizona->dev, "Spurious HPDET IRQ\n");
		mutex_unlock(&info->lock);
		return IRQ_NONE;
	}

	/* If the cable was removed while measuring ignore the result */
	ret = extcon_get_state(info->edev, EXTCON_MECHANICAL);
	if (ret < 0) {
		dev_err(arizona->dev, "Failed to check cable state: %d\n",
			ret);
		goto out;
	} else if (!ret) {
		dev_dbg(arizona->dev, "Ignoring HPDET for removed cable\n");
		goto done;
	}

	ret = arizona_hpdet_read(info);
	if (ret == -EAGAIN)
		goto out;
	else if (ret < 0)
		goto done;
	reading = ret;

	/* Reset back to starting range */
	regmap_update_bits(arizona->regmap,
			   ARIZONA_HEADPHONE_DETECT_1,
			   ARIZONA_HP_IMPEDANCE_RANGE_MASK | ARIZONA_HP_POLL,
			   0);

	ret = arizona_hpdet_do_id(info, &reading, &mic);
	if (ret == -EAGAIN)
		goto out;
	else if (ret < 0)
		goto done;

	/* Report high impedence cables as line outputs */
	if (reading >= 5000)
		report = EXTCON_JACK_LINE_OUT;
	else
		report = EXTCON_JACK_HEADPHONE;

	ret = extcon_set_state_sync(info->edev, report, true);
	if (ret != 0)
		dev_err(arizona->dev, "Failed to report HP/line: %d\n",
			ret);

done:
	/* Reset back to starting range */
	regmap_update_bits(arizona->regmap,
			   ARIZONA_HEADPHONE_DETECT_1,
			   ARIZONA_HP_IMPEDANCE_RANGE_MASK | ARIZONA_HP_POLL,
			   0);

	arizona_extcon_hp_clamp(info, false);

	if (id_gpio)
		gpio_set_value_cansleep(id_gpio, 0);

	/* Revert back to MICDET mode */
	regmap_update_bits(arizona->regmap,
			   ARIZONA_ACCESSORY_DETECT_MODE_1,
			   ARIZONA_ACCDET_MODE_MASK, ARIZONA_ACCDET_MODE_MIC);

	/* If we have a mic then reenable MICDET */
	if (mic || info->mic)
		arizona_start_mic(info);

	if (info->hpdet_active) {
		pm_runtime_put_autosuspend(info->dev);
		info->hpdet_active = false;
	}

	info->hpdet_done = true;

out:
	mutex_unlock(&info->lock);

	return IRQ_HANDLED;
}