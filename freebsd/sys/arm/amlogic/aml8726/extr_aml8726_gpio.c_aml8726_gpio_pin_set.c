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
typedef  int uint32_t ;
struct aml8726_gpio_softc {int npins; int /*<<< orphan*/ * res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_GPIO_LOCK (struct aml8726_gpio_softc*) ; 
 int /*<<< orphan*/  AML_GPIO_OUT_REG ; 
 int /*<<< orphan*/  AML_GPIO_UNLOCK (struct aml8726_gpio_softc*) ; 
 int CSR_READ_4 (struct aml8726_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_gpio_softc*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 struct aml8726_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_gpio_pin_set(device_t dev, uint32_t pin, unsigned int value)
{
	struct aml8726_gpio_softc *sc = device_get_softc(dev);
	uint32_t mask;

	if (pin >= sc->npins || value > 1)
		return (EINVAL);

	/*
	 * The GPIOAO OUT bits occupy the upper word of the OEN register.
	 */
	if (rman_get_start(sc->res[1]) == rman_get_start(sc->res[0]))
		pin += 16;

	mask = 1U << pin;

	AML_GPIO_LOCK(sc);

	CSR_WRITE_4(sc, AML_GPIO_OUT_REG,
	    ((CSR_READ_4(sc, AML_GPIO_OUT_REG) & ~mask) | (value << pin)));

	AML_GPIO_UNLOCK(sc);

	return (0);
}