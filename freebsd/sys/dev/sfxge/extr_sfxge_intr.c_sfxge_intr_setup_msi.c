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
struct sfxge_intr {int n_alloc; int /*<<< orphan*/  type; struct sfxge_intr_hdl* table; } ;
struct sfxge_softc {struct sfxge_intr intr; int /*<<< orphan*/  dev; } ;
struct sfxge_intr_hdl {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_INTR_MESSAGE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_msi_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 scalar_t__ sfxge_intr_alloc (struct sfxge_softc*,int) ; 

__attribute__((used)) static int
sfxge_intr_setup_msi(struct sfxge_softc *sc)
{
	struct sfxge_intr_hdl *table;
	struct sfxge_intr *intr;
	device_t dev;
	int count;
	int error;

	dev = sc->dev;
	intr = &sc->intr;
	table = intr->table;

	/*
	 * Check if MSI is available.  All messages must be written to
	 * the same address and on x86 this means the IRQs have the
	 * same CPU affinity.  So we only ever allocate 1.
	 */
	count = pci_msi_count(dev) ? 1 : 0;
	if (count == 0)
		return (EINVAL);

	if ((error = pci_alloc_msi(dev, &count)) != 0)
		return (ENOMEM);

	/* Allocate interrupt handler. */
	if (sfxge_intr_alloc(sc, count) != 0) {
		pci_release_msi(dev);
		return (ENOMEM);
	}

	intr->type = EFX_INTR_MESSAGE;
	intr->n_alloc = count;

	return (0);
}