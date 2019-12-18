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
typedef  size_t uint32_t ;
struct nct_softc {TYPE_1__* pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int gp_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_LOCK (struct nct_softc*) ; 
 int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct nct_softc*) ; 
 int /*<<< orphan*/  NCT_IS_VALID_PIN (size_t) ; 
 struct nct_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nct_write_pin (struct nct_softc*,size_t,size_t) ; 

__attribute__((used)) static int
nct_gpio_pin_set(device_t dev, uint32_t pin_num, uint32_t pin_value)
{
	struct nct_softc *sc;

	if (!NCT_IS_VALID_PIN(pin_num))
		return (EINVAL);

	sc = device_get_softc(dev);
	GPIO_LOCK(sc);
	if ((sc->pins[pin_num].gp_flags & GPIO_PIN_OUTPUT) == 0) {
		GPIO_UNLOCK(sc);
		return (EINVAL);
	}
	nct_write_pin(sc, pin_num, pin_value);
	GPIO_UNLOCK(sc);

	return (0);
}