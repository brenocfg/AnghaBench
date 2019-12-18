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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  ac_timer; int /*<<< orphan*/  chrg_full_timer; TYPE_1__* machinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* exit ) () ;scalar_t__ gpio_acin; scalar_t__ gpio_batfull; scalar_t__ gpio_batlock; scalar_t__ batfull_irq; scalar_t__ gpio_fatal; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_battery_percentage ; 
 int /*<<< orphan*/  dev_attr_battery_voltage ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 int /*<<< orphan*/  gpio_to_irq (scalar_t__) ; 
 int /*<<< orphan*/  led_trigger_unregister_simple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sharpsl_ac_isr ; 
 int /*<<< orphan*/  sharpsl_charge_led_trigger ; 
 int /*<<< orphan*/  sharpsl_chrg_full_isr ; 
 int /*<<< orphan*/  sharpsl_fatal_isr ; 
 TYPE_2__ sharpsl_pm ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  suspend_set_ops (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sharpsl_pm_remove(struct platform_device *pdev)
{
	suspend_set_ops(NULL);

	device_remove_file(&pdev->dev, &dev_attr_battery_percentage);
	device_remove_file(&pdev->dev, &dev_attr_battery_voltage);

	led_trigger_unregister_simple(sharpsl_charge_led_trigger);

	free_irq(gpio_to_irq(sharpsl_pm.machinfo->gpio_acin), sharpsl_ac_isr);
	free_irq(gpio_to_irq(sharpsl_pm.machinfo->gpio_batlock), sharpsl_fatal_isr);

	if (sharpsl_pm.machinfo->gpio_fatal)
		free_irq(gpio_to_irq(sharpsl_pm.machinfo->gpio_fatal), sharpsl_fatal_isr);

	if (sharpsl_pm.machinfo->batfull_irq)
		free_irq(gpio_to_irq(sharpsl_pm.machinfo->gpio_batfull), sharpsl_chrg_full_isr);

	gpio_free(sharpsl_pm.machinfo->gpio_batlock);
	gpio_free(sharpsl_pm.machinfo->gpio_batfull);
	gpio_free(sharpsl_pm.machinfo->gpio_acin);

	if (sharpsl_pm.machinfo->exit)
		sharpsl_pm.machinfo->exit();

	del_timer_sync(&sharpsl_pm.chrg_full_timer);
	del_timer_sync(&sharpsl_pm.ac_timer);

	return 0;
}