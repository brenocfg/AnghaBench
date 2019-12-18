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
struct pci_vtcon_softc {int /*<<< orphan*/  vsc_vs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  vi_reset_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pci_vtcon_reset(void *vsc)
{
	struct pci_vtcon_softc *sc;

	sc = vsc;

	DPRINTF(("vtcon: device reset requested!\n"));
	vi_reset_dev(&sc->vsc_vs);
}