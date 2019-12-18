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
struct pci_vtblk_softc {int /*<<< orphan*/  vbsc_vs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  vi_reset_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pci_vtblk_reset(void *vsc)
{
	struct pci_vtblk_softc *sc = vsc;

	DPRINTF(("vtblk: device reset requested !\n"));
	vi_reset_dev(&sc->vbsc_vs);
}