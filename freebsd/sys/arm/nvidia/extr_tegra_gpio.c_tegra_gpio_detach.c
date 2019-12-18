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
struct tegra_gpio_softc {int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ ** irq_res; int /*<<< orphan*/ * isrcs; int /*<<< orphan*/ ** irq_ih; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_LOCK_DESTROY (struct tegra_gpio_softc*) ; 
 int GPIO_NUM_BANKS ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tegra_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_detach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_gpio_pic_detach (struct tegra_gpio_softc*) ; 

__attribute__((used)) static int
tegra_gpio_detach(device_t dev)
{
	struct tegra_gpio_softc *sc;
	int i;

	sc = device_get_softc(dev);

	KASSERT(mtx_initialized(&sc->mtx), ("gpio mutex not initialized"));

	for (i = 0; i < GPIO_NUM_BANKS; i++) {
		if (sc->irq_ih[i] != NULL)
			bus_teardown_intr(dev, sc->irq_res[i], sc->irq_ih[i]);
	}

	if (sc->isrcs != NULL)
		tegra_gpio_pic_detach(sc);

	gpiobus_detach_bus(dev);

	for (i = 0; i < GPIO_NUM_BANKS; i++) {
		if (sc->irq_res[i] != NULL)
			bus_release_resource(dev, SYS_RES_IRQ, 0,
			    sc->irq_res[i]);
	}
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);
	GPIO_LOCK_DESTROY(sc);

	return(0);
}