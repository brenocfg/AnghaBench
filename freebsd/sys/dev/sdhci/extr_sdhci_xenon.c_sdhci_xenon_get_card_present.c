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
struct sdhci_xenon_softc {int /*<<< orphan*/  gpio; } ;
struct sdhci_slot {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct sdhci_xenon_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int sdhci_fdt_gpio_get_present (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
sdhci_xenon_get_card_present(device_t dev, struct sdhci_slot *slot)
{
	struct sdhci_xenon_softc *sc = device_get_softc(dev);

	return (sdhci_fdt_gpio_get_present(sc->gpio));
}