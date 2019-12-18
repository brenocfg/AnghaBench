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
struct twa_softc {int /*<<< orphan*/  intr_handle; scalar_t__ irq_res; int /*<<< orphan*/  bus_dev; } ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int bus_setup_intr (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct twa_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twa_pci_intr ; 

int twa_setup_intr(struct twa_softc *sc)
{
	int error = 0;

	if (!(sc->intr_handle) && (sc->irq_res)) {
		error = bus_setup_intr(sc->bus_dev, sc->irq_res,
					INTR_TYPE_CAM | INTR_MPSAFE,
					NULL, twa_pci_intr,
					sc, &sc->intr_handle);
	}
	return( error );
}