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
struct pio_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  ih; int /*<<< orphan*/ * res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ *) ; 
 struct pio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
pio_setup_irq(device_t dev, void *intr_handler, void *ih_user)
{
	struct pio_softc *sc;

	sc = device_get_softc(dev);

	/* Setup interrupt handlers */
	if (bus_setup_intr(sc->dev, sc->res[1], INTR_TYPE_BIO | INTR_MPSAFE,
		NULL, intr_handler, ih_user, &sc->ih)) {
		device_printf(sc->dev, "Unable to setup intr\n");
		return (1);
	}

	return (0);
}