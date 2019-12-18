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
struct lance_softc {int dummy; } ;
struct TYPE_2__ {struct lance_softc lsc; } ;
struct le_isa_softc {int /*<<< orphan*/ * sc_rres; int /*<<< orphan*/  sc_rdp; int /*<<< orphan*/  sc_rap; TYPE_1__ sc_am7990; } ;
struct le_isa_param {int /*<<< orphan*/  rdp; int /*<<< orphan*/  rap; int /*<<< orphan*/  iosize; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 scalar_t__ LE_C0_STOP ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int /*<<< orphan*/  LE_CSR3 ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/ * bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct le_isa_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ le_isa_rdcsr (struct lance_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_isa_wrcsr (struct lance_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
le_isa_probe_legacy(device_t dev, const struct le_isa_param *leip)
{
	struct le_isa_softc *lesc;
	struct lance_softc *sc;
	int error, i;

	lesc = device_get_softc(dev);
	sc = &lesc->sc_am7990.lsc;

	i = 0;
	lesc->sc_rres = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT, &i,
	    leip->iosize, RF_ACTIVE);
	if (lesc->sc_rres == NULL)
		return (ENXIO);
	lesc->sc_rap = leip->rap;
	lesc->sc_rdp = leip->rdp;

	/* Stop the chip and put it in a known state. */
	le_isa_wrcsr(sc, LE_CSR0, LE_C0_STOP);
	DELAY(100);
	if (le_isa_rdcsr(sc, LE_CSR0) != LE_C0_STOP) {
		error = ENXIO;
		goto fail;
	}
	le_isa_wrcsr(sc, LE_CSR3, 0);
	error = 0;

 fail:
	bus_release_resource(dev, SYS_RES_IOPORT,
	    rman_get_rid(lesc->sc_rres), lesc->sc_rres);
	return (error);
}