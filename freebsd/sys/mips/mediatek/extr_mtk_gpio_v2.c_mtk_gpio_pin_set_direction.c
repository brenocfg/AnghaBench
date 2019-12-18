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
typedef  unsigned int uint32_t ;
struct mtk_gpio_softc {TYPE_1__* pins; } ;
struct TYPE_2__ {unsigned int pin_caps; unsigned int pin_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int GPIO_PIN_INPUT ; 
 unsigned int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PIODIR (struct mtk_gpio_softc*) ; 
 unsigned int MTK_READ_4 (struct mtk_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_WRITE_4 (struct mtk_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
mtk_gpio_pin_set_direction(struct mtk_gpio_softc *sc, uint32_t pin,
    uint32_t dir)
{
	uint32_t regval, mask = (1u << pin);

	if (!(sc->pins[pin].pin_caps & dir))
		return (EINVAL);

	regval = MTK_READ_4(sc, GPIO_PIODIR(sc));
	if (dir == GPIO_PIN_INPUT)
		regval &= ~mask;
	else
		regval |= mask;
	MTK_WRITE_4(sc, GPIO_PIODIR(sc), regval);

	sc->pins[pin].pin_flags &= ~(GPIO_PIN_INPUT | GPIO_PIN_OUTPUT);
	sc->pins[pin].pin_flags |= dir;

	return (0);
}