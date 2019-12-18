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
struct sdhci_fdt_softc {int num_slots; int /*<<< orphan*/ * slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdhci_generic_intr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sdhci_fdt_intr(void *arg)
{
	struct sdhci_fdt_softc *sc = (struct sdhci_fdt_softc *)arg;
	int i;

	for (i = 0; i < sc->num_slots; i++)
		sdhci_generic_intr(&sc->slots[i]);
}