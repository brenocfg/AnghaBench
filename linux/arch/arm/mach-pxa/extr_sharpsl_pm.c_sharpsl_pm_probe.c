#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* platform_data; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  ac_timer; TYPE_3__* dev; TYPE_1__* machinfo; int /*<<< orphan*/  chrg_full_timer; scalar_t__ flags; int /*<<< orphan*/  charge_mode; } ;
struct TYPE_6__ {scalar_t__ gpio_batfull; scalar_t__ batfull_irq; scalar_t__ gpio_fatal; scalar_t__ gpio_batlock; scalar_t__ gpio_acin; int /*<<< orphan*/  (* init ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHRG_OFF ; 
 int EINVAL ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  apm_get_power_status ; 
 int /*<<< orphan*/  dev_attr_battery_percentage ; 
 int /*<<< orphan*/  dev_attr_battery_voltage ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,int) ; 
 int device_create_file (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_direction_input (scalar_t__) ; 
 int /*<<< orphan*/  gpio_request (scalar_t__,char*) ; 
 int gpio_to_irq (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  led_trigger_register_simple (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sharpsl_ac_isr ; 
 int /*<<< orphan*/  sharpsl_ac_timer ; 
 int /*<<< orphan*/  sharpsl_apm_get_power_status ; 
 int /*<<< orphan*/  sharpsl_charge_led_trigger ; 
 int /*<<< orphan*/  sharpsl_chrg_full_isr ; 
 int /*<<< orphan*/  sharpsl_chrg_full_timer ; 
 int /*<<< orphan*/  sharpsl_fatal_isr ; 
 TYPE_2__ sharpsl_pm ; 
 int /*<<< orphan*/  sharpsl_pm_ops ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  suspend_set_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sharpsl_pm_probe(struct platform_device *pdev)
{
	int ret, irq;

	if (!pdev->dev.platform_data)
		return -EINVAL;

	sharpsl_pm.dev = &pdev->dev;
	sharpsl_pm.machinfo = pdev->dev.platform_data;
	sharpsl_pm.charge_mode = CHRG_OFF;
	sharpsl_pm.flags = 0;

	timer_setup(&sharpsl_pm.ac_timer, sharpsl_ac_timer, 0);

	timer_setup(&sharpsl_pm.chrg_full_timer, sharpsl_chrg_full_timer, 0);

	led_trigger_register_simple("sharpsl-charge", &sharpsl_charge_led_trigger);

	sharpsl_pm.machinfo->init();

	gpio_request(sharpsl_pm.machinfo->gpio_acin, "AC IN");
	gpio_direction_input(sharpsl_pm.machinfo->gpio_acin);
	gpio_request(sharpsl_pm.machinfo->gpio_batfull, "Battery Full");
	gpio_direction_input(sharpsl_pm.machinfo->gpio_batfull);
	gpio_request(sharpsl_pm.machinfo->gpio_batlock, "Battery Lock");
	gpio_direction_input(sharpsl_pm.machinfo->gpio_batlock);

	/* Register interrupt handlers */
	irq = gpio_to_irq(sharpsl_pm.machinfo->gpio_acin);
	if (request_irq(irq, sharpsl_ac_isr, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "AC Input Detect", sharpsl_ac_isr)) {
		dev_err(sharpsl_pm.dev, "Could not get irq %d.\n", irq);
	}

	irq = gpio_to_irq(sharpsl_pm.machinfo->gpio_batlock);
	if (request_irq(irq, sharpsl_fatal_isr, IRQF_TRIGGER_FALLING, "Battery Cover", sharpsl_fatal_isr)) {
		dev_err(sharpsl_pm.dev, "Could not get irq %d.\n", irq);
	}

	if (sharpsl_pm.machinfo->gpio_fatal) {
		irq = gpio_to_irq(sharpsl_pm.machinfo->gpio_fatal);
		if (request_irq(irq, sharpsl_fatal_isr, IRQF_TRIGGER_FALLING, "Fatal Battery", sharpsl_fatal_isr)) {
			dev_err(sharpsl_pm.dev, "Could not get irq %d.\n", irq);
		}
	}

	if (sharpsl_pm.machinfo->batfull_irq) {
		/* Register interrupt handler. */
		irq = gpio_to_irq(sharpsl_pm.machinfo->gpio_batfull);
		if (request_irq(irq, sharpsl_chrg_full_isr, IRQF_TRIGGER_RISING, "CO", sharpsl_chrg_full_isr)) {
			dev_err(sharpsl_pm.dev, "Could not get irq %d.\n", irq);
		}
	}

	ret = device_create_file(&pdev->dev, &dev_attr_battery_percentage);
	ret |= device_create_file(&pdev->dev, &dev_attr_battery_voltage);
	if (ret != 0)
		dev_warn(&pdev->dev, "Failed to register attributes (%d)\n", ret);

	apm_get_power_status = sharpsl_apm_get_power_status;

#ifdef CONFIG_PM
	suspend_set_ops(&sharpsl_pm_ops);
#endif

	mod_timer(&sharpsl_pm.ac_timer, jiffies + msecs_to_jiffies(250));

	return 0;
}