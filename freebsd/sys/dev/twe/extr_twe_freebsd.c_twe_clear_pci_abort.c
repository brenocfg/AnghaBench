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
struct twe_softc {int /*<<< orphan*/  twe_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_STATUS ; 
 int /*<<< orphan*/  TWE_CONTROL (struct twe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWE_CONTROL_CLEAR_PCI_ABORT ; 
 int /*<<< orphan*/  TWE_PCI_CLEAR_PCI_ABORT ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
twe_clear_pci_abort(struct twe_softc *sc)
{
    TWE_CONTROL(sc, TWE_CONTROL_CLEAR_PCI_ABORT);
    pci_write_config(sc->twe_dev, PCIR_STATUS, TWE_PCI_CLEAR_PCI_ABORT, 2);
}