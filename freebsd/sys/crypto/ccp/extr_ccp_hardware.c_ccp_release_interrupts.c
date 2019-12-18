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
struct ccp_softc {unsigned int intr_count; int /*<<< orphan*/  dev; int /*<<< orphan*/ ** intr_res; int /*<<< orphan*/ ** intr_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ccp_release_interrupts(struct ccp_softc *sc)
{
	unsigned i;

	for (i = 0; i < sc->intr_count; i++) {
		if (sc->intr_tag[i] != NULL)
			bus_teardown_intr(sc->dev, sc->intr_res[i],
			    sc->intr_tag[i]);
		if (sc->intr_res[i] != NULL)
			bus_release_resource(sc->dev, SYS_RES_IRQ,
			    rman_get_rid(sc->intr_res[i]), sc->intr_res[i]);
	}

	pci_release_msi(sc->dev);
}