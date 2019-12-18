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
struct sdhci_fdt_gpio {int wp_inverted; int /*<<< orphan*/ * wp_pin; TYPE_1__* slot; scalar_t__ wp_disabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_pin_is_active (int /*<<< orphan*/ *,int*) ; 
 int sdhci_generic_get_ro (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sdhci_fdt_gpio_get_readonly(struct sdhci_fdt_gpio *gpio)
{
	bool pinstate;

	if (gpio->wp_disabled)
		return (false);

	if (gpio->wp_pin == NULL)
		return (sdhci_generic_get_ro(gpio->slot->bus, gpio->slot->dev));

	gpio_pin_is_active(gpio->wp_pin, &pinstate);

	return (pinstate ^ gpio->wp_inverted);
}