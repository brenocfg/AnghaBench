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
struct ti_sdhci_softc {int /*<<< orphan*/  gpio; scalar_t__ disable_readonly; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ti_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int sdhci_fdt_gpio_get_readonly (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_sdhci_get_ro(device_t brdev, device_t reqdev)
{
	struct ti_sdhci_softc *sc = device_get_softc(brdev);

	if (sc->disable_readonly)
		return (0);

	return (sdhci_fdt_gpio_get_readonly(sc->gpio));
}