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
struct ar8xxx_priv {struct ar8327_data* chip_data; } ;
struct ar8327_led_info {scalar_t__ led_num; scalar_t__ mode; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; int /*<<< orphan*/  active_low; } ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  blink_set; int /*<<< orphan*/  brightness_set; } ;
struct ar8327_led {scalar_t__ led_num; scalar_t__ mode; int enable_hw_mode; char* name; int /*<<< orphan*/  led_work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; TYPE_1__ cdev; int /*<<< orphan*/  active_low; struct ar8xxx_priv* sw_priv; } ;
struct ar8327_data {int /*<<< orphan*/  num_leds; struct ar8327_led** leds; } ;

/* Variables and functions */
 scalar_t__ AR8327_LED_MODE_HW ; 
 scalar_t__ AR8327_NUM_LEDS ; 
 int /*<<< orphan*/  CONFIG_AR8216_PHY_LEDS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8327_led_blink_set ; 
 int ar8327_led_register (struct ar8327_led*) ; 
 int /*<<< orphan*/  ar8327_led_set_brightness ; 
 int /*<<< orphan*/  ar8327_led_work_func ; 
 int /*<<< orphan*/  kfree (struct ar8327_led*) ; 
 struct ar8327_led* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar8327_led_create(struct ar8xxx_priv *priv,
		  const struct ar8327_led_info *led_info)
{
	struct ar8327_data *data = priv->chip_data;
	struct ar8327_led *aled;
	int ret;

	if (!IS_ENABLED(CONFIG_AR8216_PHY_LEDS))
		return 0;

	if (!led_info->name)
		return -EINVAL;

	if (led_info->led_num >= AR8327_NUM_LEDS)
		return -EINVAL;

	aled = kzalloc(sizeof(*aled) + strlen(led_info->name) + 1,
		       GFP_KERNEL);
	if (!aled)
		return -ENOMEM;

	aled->sw_priv = priv;
	aled->led_num = led_info->led_num;
	aled->active_low = led_info->active_low;
	aled->mode = led_info->mode;

	if (aled->mode == AR8327_LED_MODE_HW)
		aled->enable_hw_mode = true;

	aled->name = (char *)(aled + 1);
	strcpy(aled->name, led_info->name);

	aled->cdev.name = aled->name;
	aled->cdev.brightness_set = ar8327_led_set_brightness;
	aled->cdev.blink_set = ar8327_led_blink_set;
	aled->cdev.default_trigger = led_info->default_trigger;

	spin_lock_init(&aled->lock);
	mutex_init(&aled->mutex);
	INIT_WORK(&aled->led_work, ar8327_led_work_func);

	ret = ar8327_led_register(aled);
	if (ret)
		goto err_free;

	data->leds[data->num_leds++] = aled;

	return 0;

err_free:
	kfree(aled);
	return ret;
}