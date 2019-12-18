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
struct vtpci_softc {int /*<<< orphan*/  vtpci_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTPCI_FLAG_LEGACY ; 

__attribute__((used)) static int
vtpci_alloc_intr_legacy(struct vtpci_softc *sc)
{

	sc->vtpci_flags |= VTPCI_FLAG_LEGACY;

	return (0);
}