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
struct ti_sdhci_softc {int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdhci_generic_intr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ti_sdhci_intr(void *arg)
{
	struct ti_sdhci_softc *sc = arg;

	sdhci_generic_intr(&sc->slot);
}