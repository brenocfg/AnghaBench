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
struct resource {int dummy; } ;
struct fhc_softc {scalar_t__ sc_ign; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * iv_ic; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INTIGN (size_t) ; 
 int bus_generic_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void**) ; 
 struct fhc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  fhc_ic ; 
 TYPE_1__* intr_vectors ; 
 size_t rman_get_start (struct resource*) ; 

__attribute__((used)) static int
fhc_setup_intr(device_t bus, device_t child, struct resource *r, int flags,
    driver_filter_t *filt, driver_intr_t *func, void *arg, void **cookiep)
{
	struct fhc_softc *sc;
	u_long vec;

	sc = device_get_softc(bus);
	/*
	 * Make sure the vector is fully specified and we registered
	 * our interrupt controller for it.
	 */
	vec = rman_get_start(r);
	if (INTIGN(vec) != sc->sc_ign || intr_vectors[vec].iv_ic != &fhc_ic) {
		device_printf(bus, "invalid interrupt vector 0x%lx\n", vec);
		return (EINVAL);
	}
	return (bus_generic_setup_intr(bus, child, r, flags, filt, func,
	    arg, cookiep));
}