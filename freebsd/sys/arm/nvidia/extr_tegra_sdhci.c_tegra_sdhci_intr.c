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
struct tegra_sdhci_softc {int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  RD4 (struct tegra_sdhci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDHCI_INT_STATUS ; 
 int /*<<< orphan*/  sdhci_generic_intr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tegra_sdhci_intr(void *arg)
{
	struct tegra_sdhci_softc *sc = arg;

	sdhci_generic_intr(&sc->slot);
	RD4(sc, SDHCI_INT_STATUS);
}