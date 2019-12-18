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
struct octeon_gpio_softc {int /*<<< orphan*/  gpio_mtx; scalar_t__* gpio_irq_res; int /*<<< orphan*/ * gpio_irq_rid; scalar_t__* gpio_ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int OCTEON_GPIO_IRQS ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct octeon_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_detach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
octeon_gpio_detach(device_t dev)
{
	struct octeon_gpio_softc *sc = device_get_softc(dev);
	int i;

	KASSERT(mtx_initialized(&sc->gpio_mtx), ("gpio mutex not initialized"));

	for ( i = 0; i < OCTEON_GPIO_IRQS; i++) {
		if (sc->gpio_ih[i])
			bus_teardown_intr(dev, sc->gpio_irq_res[i],
			    sc->gpio_ih[i]);
		if (sc->gpio_irq_res[i])
			bus_release_resource(dev, SYS_RES_IRQ,
			    sc->gpio_irq_rid[i], sc->gpio_irq_res[i]);
	}
	gpiobus_detach_bus(dev);
	mtx_destroy(&sc->gpio_mtx);

	return(0);
}