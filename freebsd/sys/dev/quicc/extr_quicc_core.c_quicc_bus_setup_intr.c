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
struct quicc_softc {int /*<<< orphan*/  sc_icookie; int /*<<< orphan*/  sc_ires; scalar_t__ sc_fastintr; scalar_t__ sc_polled; } ;
struct quicc_device {void* qd_ih_arg; int /*<<< orphan*/ * qd_ih; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_TTY ; 
 int /*<<< orphan*/  bus_setup_intr (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct quicc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct quicc_device* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct quicc_softc* device_get_softc (scalar_t__) ; 
 scalar_t__ quicc_bfe_intr ; 

int
quicc_bus_setup_intr(device_t dev, device_t child, struct resource *r,
    int flags, driver_filter_t *filt, void (*ihand)(void *), void *arg,
    void **cookiep)
{
	struct quicc_device *qd;
	struct quicc_softc *sc;

	if (device_get_parent(child) != dev)
		return (EINVAL);

	/* Interrupt handlers must be FAST or MPSAFE. */
	if (filt == NULL && !(flags & INTR_MPSAFE))
		return (EINVAL);

	sc = device_get_softc(dev);
	if (sc->sc_polled)
		return (ENXIO);

	if (sc->sc_fastintr && filt == NULL) {
		sc->sc_fastintr = 0;
		bus_teardown_intr(dev, sc->sc_ires, sc->sc_icookie);
		bus_setup_intr(dev, sc->sc_ires, INTR_TYPE_TTY | INTR_MPSAFE,
		    NULL, (driver_intr_t *)quicc_bfe_intr, sc, &sc->sc_icookie);
	}

	qd = device_get_ivars(child);
	qd->qd_ih = (filt != NULL) ? filt : (driver_filter_t *)ihand;
	qd->qd_ih_arg = arg;
	*cookiep = ihand;
	return (0);
}