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
struct sec_softc {int /*<<< orphan*/  sc_dev; } ;
struct resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int bus_teardown_intr (int /*<<< orphan*/ ,struct resource*,void*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*,int) ; 

__attribute__((used)) static void
sec_release_intr(struct sec_softc *sc, struct resource *ires, void *ihand,
    int irid, const char *iname)
{
	int error;

	if (ires == NULL)
		return;

	error = bus_teardown_intr(sc->sc_dev, ires, ihand);
	if (error)
		device_printf(sc->sc_dev, "bus_teardown_intr() failed for %s"
		    " IRQ, error %d\n", iname, error);

	error = bus_release_resource(sc->sc_dev, SYS_RES_IRQ, irid, ires);
	if (error)
		device_printf(sc->sc_dev, "bus_release_resource() failed for %s"
		    " IRQ, error %d\n", iname, error);
}