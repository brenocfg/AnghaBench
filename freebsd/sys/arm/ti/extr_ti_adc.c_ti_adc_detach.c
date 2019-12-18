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
struct ti_adc_softc {scalar_t__ sc_mem_res; scalar_t__ sc_irq_res; scalar_t__ sc_intrhand; int /*<<< orphan*/  sc_evdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TI_ADC_LOCK (struct ti_adc_softc*) ; 
 int /*<<< orphan*/  TI_ADC_LOCK_DESTROY (struct ti_adc_softc*) ; 
 int /*<<< orphan*/  TI_ADC_UNLOCK (struct ti_adc_softc*) ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct ti_adc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_adc_reset (struct ti_adc_softc*) ; 
 int /*<<< orphan*/  ti_adc_setup (struct ti_adc_softc*) ; 

__attribute__((used)) static int
ti_adc_detach(device_t dev)
{
	struct ti_adc_softc *sc;

	sc = device_get_softc(dev);

	/* Turn off the ADC. */
	TI_ADC_LOCK(sc);
	ti_adc_reset(sc);
	ti_adc_setup(sc);

#ifdef EVDEV_SUPPORT
	evdev_free(sc->sc_evdev);
#endif

	TI_ADC_UNLOCK(sc);

	TI_ADC_LOCK_DESTROY(sc);

	if (sc->sc_intrhand)
		bus_teardown_intr(dev, sc->sc_irq_res, sc->sc_intrhand);
	if (sc->sc_irq_res)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq_res);
	if (sc->sc_mem_res)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);

	return (bus_generic_detach(dev));
}