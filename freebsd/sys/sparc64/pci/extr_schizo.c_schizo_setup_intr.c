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
typedef  size_t u_long ;
struct schizo_softc {scalar_t__ sc_ign; } ;
struct schizo_icarg {struct schizo_softc* sica_sc; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * iv_ic; scalar_t__ iv_icarg; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INTIGN (size_t) ; 
 int /*<<< orphan*/  INTINO (size_t) ; 
 scalar_t__ bootverbose ; 
 int bus_generic_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void**) ; 
 struct schizo_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t,...) ; 
 TYPE_1__* intr_vectors ; 
 size_t rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  schizo_ic ; 
 int schizo_intr_register (struct schizo_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
schizo_setup_intr(device_t dev, device_t child, struct resource *ires,
    int flags, driver_filter_t *filt, driver_intr_t *intr, void *arg,
    void **cookiep)
{
	struct schizo_softc *sc;
	u_long vec;
	int error;

	sc = device_get_softc(dev);
	/*
	 * Make sure the vector is fully specified.
	 */
	vec = rman_get_start(ires);
	if (INTIGN(vec) != sc->sc_ign) {
		device_printf(dev, "invalid interrupt vector 0x%lx\n", vec);
		return (EINVAL);
	}

	if (intr_vectors[vec].iv_ic == &schizo_ic) {
		/*
		 * Ensure we use the right softc in case the interrupt
		 * is routed to our companion PBM for some odd reason.
		 */
		sc = ((struct schizo_icarg *)intr_vectors[vec].iv_icarg)->
		    sica_sc;
	} else if (intr_vectors[vec].iv_ic == NULL) {
		/*
		 * Work around broken firmware which misses entries in
		 * the ino-bitmap.
		 */
		error = schizo_intr_register(sc, INTINO(vec));
		if (error != 0) {
			device_printf(dev, "could not register interrupt "
			    "controller for vector 0x%lx (%d)\n", vec, error);
			return (error);
		}
		if (bootverbose)
			device_printf(dev, "belatedly registered as "
			    "interrupt controller for vector 0x%lx\n", vec);
	} else {
		device_printf(dev,
		    "invalid interrupt controller for vector 0x%lx\n", vec);
		return (EINVAL);
	}
	return (bus_generic_setup_intr(dev, child, ires, flags, filt, intr,
	    arg, cookiep));
}