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
struct sdhci_fdt_gpio {int /*<<< orphan*/ * cd_ires; int /*<<< orphan*/  dev; int /*<<< orphan*/ * cd_pin; int /*<<< orphan*/ * wp_pin; int /*<<< orphan*/ * cd_ihandler; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct sdhci_fdt_gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_pin_release (int /*<<< orphan*/ *) ; 

void
sdhci_fdt_gpio_teardown(struct sdhci_fdt_gpio *gpio)
{

	if (gpio == NULL)
		return;

	if (gpio->cd_ihandler != NULL)
		bus_teardown_intr(gpio->dev, gpio->cd_ires, gpio->cd_ihandler);
	if (gpio->wp_pin != NULL)
		gpio_pin_release(gpio->wp_pin);
	if (gpio->cd_pin != NULL)
		gpio_pin_release(gpio->cd_pin);
	if (gpio->cd_ires != NULL)
		bus_release_resource(gpio->dev, SYS_RES_IRQ, 0, gpio->cd_ires);

	free(gpio, M_DEVBUF);
}