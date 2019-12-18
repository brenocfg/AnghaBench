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
struct am335x_rtc_softc {scalar_t__ sc_mem_res; int /*<<< orphan*/ ** sc_irq_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_LOCK_DESTROY (struct am335x_rtc_softc*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  am335x_rtc_irq_spec ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 struct am335x_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
am335x_rtc_detach(device_t dev)
{
	struct am335x_rtc_softc *sc;

	sc = device_get_softc(dev);
	if (sc->sc_irq_res[0] != NULL)
		bus_release_resources(dev, am335x_rtc_irq_spec, sc->sc_irq_res);
	if (sc->sc_mem_res)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);
	RTC_LOCK_DESTROY(sc);

	return (0);
}