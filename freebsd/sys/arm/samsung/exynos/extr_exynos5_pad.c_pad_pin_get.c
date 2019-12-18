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
typedef  int /*<<< orphan*/  uint32_t ;
struct pad_softc {int gpio_npins; TYPE_1__* gpio_pins; } ;
struct gpio_bank {scalar_t__ con; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  gp_pin; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_LOCK (struct pad_softc*) ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct pad_softc*) ; 
 int READ4 (struct pad_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct pad_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ get_bank (struct pad_softc*,int /*<<< orphan*/ ,struct gpio_bank*,int*) ; 

__attribute__((used)) static int
pad_pin_get(device_t dev, uint32_t pin, unsigned int *val)
{
	struct gpio_bank bank;
	struct pad_softc *sc;
	int pin_shift;
	int i;

	sc = device_get_softc(dev);
	for (i = 0; i < sc->gpio_npins; i++) {
		if (sc->gpio_pins[i].gp_pin == pin)
			break;
	}

	if (i >= sc->gpio_npins)
		return (EINVAL);

	if (get_bank(sc, pin, &bank, &pin_shift) != 0)
		return (EINVAL);

	GPIO_LOCK(sc);
	if (READ4(sc, bank.port, bank.con + 0x4) & (1 << pin_shift))
		*val = 1;
	else
		*val = 0;
	GPIO_UNLOCK(sc);

	return (0);
}