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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sbni_softc {int /*<<< orphan*/  irq_handle; int /*<<< orphan*/ * irq_res; TYPE_1__* ifp; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/  dev; } ;
struct sbni_flags {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sbni_softc*,int /*<<< orphan*/ *) ; 
 struct sbni_softc* connect_to_master (struct sbni_softc*) ; 
 int /*<<< orphan*/  device_get_flags (int /*<<< orphan*/ ) ; 
 struct sbni_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sbni_add (struct sbni_softc*) ; 
 int sbni_attach (struct sbni_softc*,int,struct sbni_flags) ; 
 int /*<<< orphan*/  sbni_detach (struct sbni_softc*) ; 
 int /*<<< orphan*/  sbni_intr ; 
 int /*<<< orphan*/  sbni_release_resources (struct sbni_softc*) ; 

__attribute__((used)) static int
sbni_attach_isa(device_t dev)
{
	struct sbni_softc *sc;
	struct sbni_flags flags;
	int error;
   
	sc = device_get_softc(dev);
	sc->dev = dev;

	sc->irq_res = bus_alloc_resource_any(
	    dev, SYS_RES_IRQ, &sc->irq_rid, RF_ACTIVE);

#ifndef SBNI_DUAL_COMPOUND

	if (sc->irq_res == NULL) {
		device_printf(dev, "irq conflict!\n");
		sbni_release_resources(sc);
		return (ENOENT);
	}

#else	/* SBNI_DUAL_COMPOUND */

	if (sc->irq_res) {
		sbni_add(sc);
	} else {
		struct sbni_softc  *master;

		if ((master = connect_to_master(sc)) == NULL) {
			device_printf(dev, "failed to alloc irq\n");
			sbni_release_resources(sc);
			return (ENXIO);
		} else {
			device_printf(dev, "shared irq with %s\n",
			       master->ifp->if_xname);
		}
	} 
#endif	/* SBNI_DUAL_COMPOUND */

	*(u_int32_t*)&flags = device_get_flags(dev);

	error = sbni_attach(sc, device_get_unit(dev) * 2, flags);
	if (error) {
		device_printf(dev, "cannot initialize driver\n");
		sbni_release_resources(sc);
		return (error);
	}

	if (sc->irq_res) {
		error = bus_setup_intr(
		    dev, sc->irq_res, INTR_TYPE_NET | INTR_MPSAFE,
		    NULL, sbni_intr, sc, &sc->irq_handle);
		if (error) {
			device_printf(dev, "bus_setup_intr\n");
			sbni_detach(sc);
			sbni_release_resources(sc);
			return (error);
		}
	}

	return (0);
}