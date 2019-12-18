#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bxe_softc {int interrupt_mode; int intr_count; int /*<<< orphan*/  dev; TYPE_1__* intr; } ;
struct TYPE_2__ {int /*<<< orphan*/ * resource; int /*<<< orphan*/  rid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
#define  INTR_MODE_INTX 130 
#define  INTR_MODE_MSI 129 
#define  INTR_MODE_MSIX 128 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_interrupt_free(struct bxe_softc *sc)
{
    int i;

    switch (sc->interrupt_mode) {
    case INTR_MODE_INTX:
        BLOGD(sc, DBG_LOAD, "Releasing legacy INTx vector\n");
        if (sc->intr[0].resource != NULL) {
            bus_release_resource(sc->dev,
                                 SYS_RES_IRQ,
                                 sc->intr[0].rid,
                                 sc->intr[0].resource);
        }
        break;
    case INTR_MODE_MSI:
        for (i = 0; i < sc->intr_count; i++) {
            BLOGD(sc, DBG_LOAD, "Releasing MSI vector %d\n", i);
            if (sc->intr[i].resource && sc->intr[i].rid) {
                bus_release_resource(sc->dev,
                                     SYS_RES_IRQ,
                                     sc->intr[i].rid,
                                     sc->intr[i].resource);
            }
        }
        pci_release_msi(sc->dev);
        break;
    case INTR_MODE_MSIX:
        for (i = 0; i < sc->intr_count; i++) {
            BLOGD(sc, DBG_LOAD, "Releasing MSI-X vector %d\n", i);
            if (sc->intr[i].resource && sc->intr[i].rid) {
                bus_release_resource(sc->dev,
                                     SYS_RES_IRQ,
                                     sc->intr[i].rid,
                                     sc->intr[i].resource);
            }
        }
        pci_release_msi(sc->dev);
        break;
    default:
        /* nothing to do as initial allocation failed */
        break;
    }
}