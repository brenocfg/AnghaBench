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
struct upa_softc {scalar_t__ sc_ign; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * iv_ic; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INTIGN (size_t) ; 
 int bus_generic_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void**) ; 
 struct upa_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 TYPE_1__* intr_vectors ; 
 size_t rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  upa_ic ; 

__attribute__((used)) static int
upa_setup_intr(device_t dev, device_t child, struct resource *ires, int flags,
    driver_filter_t *filt, driver_intr_t *func, void *arg, void **cookiep)
{
	struct upa_softc *sc;
	u_long vec;

	sc = device_get_softc(dev);
	/*
	 * Make sure the vector is fully specified and we registered
	 * our interrupt controller for it.
	 */
	vec = rman_get_start(ires);
	if (INTIGN(vec) != sc->sc_ign || intr_vectors[vec].iv_ic != &upa_ic) {
		device_printf(dev, "invalid interrupt vector 0x%lx\n", vec);
		return (EINVAL);
	}
	return (bus_generic_setup_intr(dev, child, ires, flags, filt, func,
	    arg, cookiep));
}