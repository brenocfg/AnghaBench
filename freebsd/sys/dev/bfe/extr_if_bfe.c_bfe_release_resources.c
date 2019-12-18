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
struct bfe_softc {int /*<<< orphan*/ * bfe_ifp; int /*<<< orphan*/ * bfe_res; int /*<<< orphan*/  bfe_dev; int /*<<< orphan*/ * bfe_irq; int /*<<< orphan*/ * bfe_intrhand; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfe_release_resources(struct bfe_softc *sc)
{

	if (sc->bfe_intrhand != NULL)
		bus_teardown_intr(sc->bfe_dev, sc->bfe_irq, sc->bfe_intrhand);

	if (sc->bfe_irq != NULL)
		bus_release_resource(sc->bfe_dev, SYS_RES_IRQ, 0, sc->bfe_irq);

	if (sc->bfe_res != NULL)
		bus_release_resource(sc->bfe_dev, SYS_RES_MEMORY, PCIR_BAR(0),
		    sc->bfe_res);

	if (sc->bfe_ifp != NULL)
		if_free(sc->bfe_ifp);
}