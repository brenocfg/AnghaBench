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
struct resource {int dummy; } ;
struct auxio_softc {int sc_nauxio; int* sc_rid; int sc_led_stat; int /*<<< orphan*/  sc_led_dev; int /*<<< orphan*/ * sc_regh; int /*<<< orphan*/ * sc_regt; struct resource** sc_res; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int AUXIO_LED_LED ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  auxio_free_resource (struct auxio_softc*) ; 
 int /*<<< orphan*/  auxio_led_func (struct auxio_softc*,int) ; 
 int auxio_led_read (struct auxio_softc*) ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  led_create (int /*<<< orphan*/  (*) (struct auxio_softc*,int),struct auxio_softc*,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 

__attribute__((used)) static int
auxio_attach_common(struct auxio_softc *sc)
{
	struct resource *res;
	int i;

	for (i = 0; i < sc->sc_nauxio; i++) {
		sc->sc_rid[i] = i;
		res = bus_alloc_resource_any(sc->sc_dev, SYS_RES_MEMORY,
		    &sc->sc_rid[i], RF_ACTIVE);
		if (res == NULL) {
			device_printf(sc->sc_dev,
			    "could not allocate resources\n");
			goto attach_fail;
		}
		sc->sc_res[i] = res;
		sc->sc_regt[i] = rman_get_bustag(res);
		sc->sc_regh[i] = rman_get_bushandle(res);
	}

	sc->sc_led_stat = auxio_led_read(sc) & AUXIO_LED_LED;
	sc->sc_led_dev = led_create(auxio_led_func, sc, "auxioled");
	/* turn on the LED */
	auxio_led_func(sc, 1);

	return (0);

attach_fail:
	auxio_free_resource(sc);

	return (ENXIO);
}