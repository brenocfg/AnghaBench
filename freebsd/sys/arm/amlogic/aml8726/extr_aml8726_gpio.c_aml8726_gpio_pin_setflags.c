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
typedef  unsigned int uint32_t ;
struct aml8726_gpio_softc {unsigned int npins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_GPIO_LOCK (struct aml8726_gpio_softc*) ; 
 int /*<<< orphan*/  AML_GPIO_OE_N_REG ; 
 int /*<<< orphan*/  AML_GPIO_UNLOCK (struct aml8726_gpio_softc*) ; 
 unsigned int CSR_READ_4 (struct aml8726_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 int EINVAL ; 
 unsigned int GPIO_PIN_OUTPUT ; 
 struct aml8726_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_gpio_pin_setflags(device_t dev, uint32_t pin, uint32_t flags)
{
	struct aml8726_gpio_softc *sc = device_get_softc(dev);
	uint32_t mask = 1U << pin;

	if (pin >= sc->npins)
		return (EINVAL);

	AML_GPIO_LOCK(sc);

	if ((flags & GPIO_PIN_OUTPUT) != 0) {
		/* Output.  Turn on driver.  */
		CSR_WRITE_4(sc, AML_GPIO_OE_N_REG,
		    (CSR_READ_4(sc, AML_GPIO_OE_N_REG) & ~mask));
	} else {
		/* Input.  Turn off driver. */
		CSR_WRITE_4(sc, AML_GPIO_OE_N_REG,
		    (CSR_READ_4(sc, AML_GPIO_OE_N_REG) | mask));
	}
		
	AML_GPIO_UNLOCK(sc);

	return (0);
}