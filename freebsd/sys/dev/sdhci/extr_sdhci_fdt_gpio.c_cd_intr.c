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
struct sdhci_fdt_gpio {int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdhci_fdt_gpio_get_present (struct sdhci_fdt_gpio*) ; 
 int /*<<< orphan*/  sdhci_handle_card_present (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cd_intr(void *arg)
{
	struct sdhci_fdt_gpio *gpio = arg;

	sdhci_handle_card_present(gpio->slot, sdhci_fdt_gpio_get_present(gpio));
}