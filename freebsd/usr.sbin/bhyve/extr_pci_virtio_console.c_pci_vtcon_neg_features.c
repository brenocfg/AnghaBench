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
typedef  int /*<<< orphan*/  uint64_t ;
struct pci_vtcon_softc {int /*<<< orphan*/  vsc_features; } ;

/* Variables and functions */

__attribute__((used)) static void
pci_vtcon_neg_features(void *vsc, uint64_t negotiated_features)
{
	struct pci_vtcon_softc *sc = vsc;

	sc->vsc_features = negotiated_features;
}