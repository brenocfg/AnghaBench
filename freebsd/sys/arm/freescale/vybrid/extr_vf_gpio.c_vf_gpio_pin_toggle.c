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
typedef  scalar_t__ uint32_t ;
struct vf_gpio_softc {int gpio_npins; TYPE_1__* gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ gp_pin; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_LOCK (struct vf_gpio_softc*) ; 
 int /*<<< orphan*/  GPIO_PTOR (int) ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct vf_gpio_softc*) ; 
 int /*<<< orphan*/  WRITE4 (struct vf_gpio_softc*,int /*<<< orphan*/ ,int) ; 
 struct vf_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vf_gpio_pin_toggle(device_t dev, uint32_t pin)
{
	struct vf_gpio_softc *sc;
	int i;

	sc = device_get_softc(dev);
	for (i = 0; i < sc->gpio_npins; i++) {
		if (sc->gpio_pins[i].gp_pin == pin)
			break;
	}

	if (i >= sc->gpio_npins)
		return (EINVAL);

	GPIO_LOCK(sc);
	WRITE4(sc, GPIO_PTOR(i), (1 << (i % 32)));
	GPIO_UNLOCK(sc);

	return (0);
}