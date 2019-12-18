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
struct an_softc {int /*<<< orphan*/  irq_handle; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  an_dev; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/  port_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_TYPE_NET ; 
 int /*<<< orphan*/  an_alloc_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  an_alloc_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int an_attach (struct an_softc*,int) ; 
 int /*<<< orphan*/  an_intr ; 
 int /*<<< orphan*/  an_release_resources (int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct an_softc*,int /*<<< orphan*/ *) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 struct an_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
an_attach_isa(device_t dev)
{
	struct an_softc *sc = device_get_softc(dev);
	int flags = device_get_flags(dev);
	int error;

	an_alloc_port(dev, sc->port_rid, 1);
	an_alloc_irq(dev, sc->irq_rid, 0);

	sc->an_dev = dev;

	error = an_attach(sc, flags);
	if (error) {
		an_release_resources(dev);
		return (error);
	}

	error = bus_setup_intr(dev, sc->irq_res, INTR_TYPE_NET,
			       NULL, an_intr, sc, &sc->irq_handle);
	if (error) {
		an_release_resources(dev);
		return (error);
	}
	return (0);
}