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
struct sdhci_fdt_gpio {int cd_inverted; int /*<<< orphan*/ * cd_pin; TYPE_1__* slot; scalar_t__ cd_disabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_pin_is_active (int /*<<< orphan*/ *,int*) ; 
 int sdhci_generic_get_card_present (int /*<<< orphan*/ ,TYPE_1__*) ; 

bool
sdhci_fdt_gpio_get_present(struct sdhci_fdt_gpio *gpio)
{
	bool pinstate;

	if (gpio->cd_disabled)
		return (true);

	if (gpio->cd_pin == NULL)
		return (sdhci_generic_get_card_present(gpio->slot->bus,
		    gpio->slot));

	gpio_pin_is_active(gpio->cd_pin, &pinstate);

	return (pinstate ^ gpio->cd_inverted);
}