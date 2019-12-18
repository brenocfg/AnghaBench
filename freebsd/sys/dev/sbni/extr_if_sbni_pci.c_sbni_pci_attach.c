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
typedef  scalar_t__ u_int32_t ;
struct sbni_softc {struct sbni_softc* slave_sc; int /*<<< orphan*/  irq_handle; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/  dev; } ;
struct sbni_flags {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sbni_softc*,int /*<<< orphan*/ *) ; 
 struct sbni_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct sbni_softc*,int /*<<< orphan*/ ) ; 
 int sbni_attach (struct sbni_softc*,int,struct sbni_flags) ; 
 int /*<<< orphan*/  sbni_detach (struct sbni_softc*) ; 
 int /*<<< orphan*/  sbni_intr ; 
 int /*<<< orphan*/  sbni_release_resources (struct sbni_softc*) ; 

__attribute__((used)) static int
sbni_pci_attach(device_t dev)
{
	struct sbni_softc *sc;
	struct sbni_flags flags;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;

	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irq_rid,
					     RF_SHAREABLE);

	if (sc->irq_res == NULL) {
		device_printf(dev, "cannot claim irq!\n");
		error = ENOENT;
		goto attach_failed;
	}

	*(u_int32_t*)&flags = 0;

	error = sbni_attach(sc, device_get_unit(dev) * 2, flags);
	if (error) {
		device_printf(dev, "cannot initialize driver\n");
		goto attach_failed;
	}
	if (sc->slave_sc) {
		error = sbni_attach(sc->slave_sc, device_get_unit(dev) * 2 + 1,
		    flags);
		if (error) {
			device_printf(dev, "cannot initialize slave\n");
			sbni_detach(sc);
			goto attach_failed;
		}
	}

	if (sc->irq_res) {
		error = bus_setup_intr(dev, sc->irq_res, INTR_TYPE_NET |
		    INTR_MPSAFE, NULL, sbni_intr, sc, &sc->irq_handle);
		if (error) {
			device_printf(dev, "bus_setup_intr\n");
			sbni_detach(sc);
			if (sc->slave_sc)
				sbni_detach(sc);
			goto attach_failed;
		}
	}
	return (0);

attach_failed:
	sbni_release_resources(sc);
	if (sc->slave_sc)
		free(sc->slave_sc, M_DEVBUF);
	return (error);
}