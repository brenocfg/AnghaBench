#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct arizona_extcon_info {unsigned int last_jackdet; int micd_timeout; int detecting; int mic; int hpdet_done; int hpdet_retried; int num_micd_ranges; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  edev; int /*<<< orphan*/  input; TYPE_1__* micd_ranges; scalar_t__* hpdet_res; scalar_t__ num_hpdet_res; scalar_t__ micd_clamp; int /*<<< orphan*/  hpdet_work; scalar_t__ jack_flips; int /*<<< orphan*/  micd_timeout_work; struct arizona* arizona; } ;
struct TYPE_4__ {int micd_timeout; scalar_t__ jd_invert; int /*<<< orphan*/  hpdet_acc_id; } ;
struct arizona {int /*<<< orphan*/  regmap; TYPE_2__ pdata; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_AOD_IRQ_RAW_STATUS ; 
 int /*<<< orphan*/  ARIZONA_AOD_WKUP_AND_TRIG ; 
 int /*<<< orphan*/  ARIZONA_JACK_DETECT_DEBOUNCE ; 
 int ARIZONA_JD1_DB ; 
 int ARIZONA_JD1_FALL_TRIG_STS ; 
 int ARIZONA_JD1_RISE_TRIG_STS ; 
 unsigned int ARIZONA_JD1_STS ; 
 int ARIZONA_MICD_CLAMP_DB ; 
 int ARIZONA_MICD_CLAMP_FALL_TRIG_STS ; 
 int ARIZONA_MICD_CLAMP_RISE_TRIG_STS ; 
 unsigned int ARIZONA_MICD_CLAMP_STS ; 
 int ARRAY_SIZE (scalar_t__*) ; 
 int DEFAULT_MICD_TIMEOUT ; 
 scalar_t__ EXTCON_MECHANICAL ; 
 int HPDET_DEBOUNCE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__* arizona_cable ; 
 int /*<<< orphan*/  arizona_hpdet_wait (struct arizona_extcon_info*) ; 
 int /*<<< orphan*/  arizona_start_mic (struct arizona_extcon_info*) ; 
 int /*<<< orphan*/  arizona_stop_mic (struct arizona_extcon_info*) ; 
 int cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int extcon_set_state_sync (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static irqreturn_t arizona_jackdet(int irq, void *data)
{
	struct arizona_extcon_info *info = data;
	struct arizona *arizona = info->arizona;
	unsigned int val, present, mask;
	bool cancelled_hp, cancelled_mic;
	int ret, i;

	cancelled_hp = cancel_delayed_work_sync(&info->hpdet_work);
	cancelled_mic = cancel_delayed_work_sync(&info->micd_timeout_work);

	pm_runtime_get_sync(info->dev);

	mutex_lock(&info->lock);

	if (info->micd_clamp) {
		mask = ARIZONA_MICD_CLAMP_STS;
		present = 0;
	} else {
		mask = ARIZONA_JD1_STS;
		if (arizona->pdata.jd_invert)
			present = 0;
		else
			present = ARIZONA_JD1_STS;
	}

	ret = regmap_read(arizona->regmap, ARIZONA_AOD_IRQ_RAW_STATUS, &val);
	if (ret != 0) {
		dev_err(arizona->dev, "Failed to read jackdet status: %d\n",
			ret);
		mutex_unlock(&info->lock);
		pm_runtime_put_autosuspend(info->dev);
		return IRQ_NONE;
	}

	val &= mask;
	if (val == info->last_jackdet) {
		dev_dbg(arizona->dev, "Suppressing duplicate JACKDET\n");
		if (cancelled_hp)
			queue_delayed_work(system_power_efficient_wq,
					   &info->hpdet_work,
					   msecs_to_jiffies(HPDET_DEBOUNCE));

		if (cancelled_mic) {
			int micd_timeout = info->micd_timeout;

			queue_delayed_work(system_power_efficient_wq,
					   &info->micd_timeout_work,
					   msecs_to_jiffies(micd_timeout));
		}

		goto out;
	}
	info->last_jackdet = val;

	if (info->last_jackdet == present) {
		dev_dbg(arizona->dev, "Detected jack\n");
		ret = extcon_set_state_sync(info->edev,
					      EXTCON_MECHANICAL, true);

		if (ret != 0)
			dev_err(arizona->dev, "Mechanical report failed: %d\n",
				ret);

		if (!arizona->pdata.hpdet_acc_id) {
			info->detecting = true;
			info->mic = false;
			info->jack_flips = 0;

			arizona_start_mic(info);
		} else {
			queue_delayed_work(system_power_efficient_wq,
					   &info->hpdet_work,
					   msecs_to_jiffies(HPDET_DEBOUNCE));
		}

		if (info->micd_clamp || !arizona->pdata.jd_invert)
			regmap_update_bits(arizona->regmap,
					   ARIZONA_JACK_DETECT_DEBOUNCE,
					   ARIZONA_MICD_CLAMP_DB |
					   ARIZONA_JD1_DB, 0);
	} else {
		dev_dbg(arizona->dev, "Detected jack removal\n");

		arizona_stop_mic(info);

		info->num_hpdet_res = 0;
		for (i = 0; i < ARRAY_SIZE(info->hpdet_res); i++)
			info->hpdet_res[i] = 0;
		info->mic = false;
		info->hpdet_done = false;
		info->hpdet_retried = false;

		for (i = 0; i < info->num_micd_ranges; i++)
			input_report_key(info->input,
					 info->micd_ranges[i].key, 0);
		input_sync(info->input);

		for (i = 0; i < ARRAY_SIZE(arizona_cable) - 1; i++) {
			ret = extcon_set_state_sync(info->edev,
					arizona_cable[i], false);
			if (ret != 0)
				dev_err(arizona->dev,
					"Removal report failed: %d\n", ret);
		}

		/*
		 * If the jack was removed during a headphone detection we
		 * need to wait for the headphone detection to finish, as
		 * it can not be aborted. We don't want to be able to start
		 * a new headphone detection from a fresh insert until this
		 * one is finished.
		 */
		arizona_hpdet_wait(info);

		regmap_update_bits(arizona->regmap,
				   ARIZONA_JACK_DETECT_DEBOUNCE,
				   ARIZONA_MICD_CLAMP_DB | ARIZONA_JD1_DB,
				   ARIZONA_MICD_CLAMP_DB | ARIZONA_JD1_DB);
	}

	if (arizona->pdata.micd_timeout)
		info->micd_timeout = arizona->pdata.micd_timeout;
	else
		info->micd_timeout = DEFAULT_MICD_TIMEOUT;

out:
	/* Clear trig_sts to make sure DCVDD is not forced up */
	regmap_write(arizona->regmap, ARIZONA_AOD_WKUP_AND_TRIG,
		     ARIZONA_MICD_CLAMP_FALL_TRIG_STS |
		     ARIZONA_MICD_CLAMP_RISE_TRIG_STS |
		     ARIZONA_JD1_FALL_TRIG_STS |
		     ARIZONA_JD1_RISE_TRIG_STS);

	mutex_unlock(&info->lock);

	pm_runtime_mark_last_busy(info->dev);
	pm_runtime_put_autosuspend(info->dev);

	return IRQ_HANDLED;
}