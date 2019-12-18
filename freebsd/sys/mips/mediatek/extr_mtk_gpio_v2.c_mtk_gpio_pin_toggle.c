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
struct mtk_gpio_softc {size_t num_pins; TYPE_1__* pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int pin_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PIODATA (struct mtk_gpio_softc*) ; 
 int /*<<< orphan*/  GPIO_PIORESET (struct mtk_gpio_softc*) ; 
 int /*<<< orphan*/  GPIO_PIOSET (struct mtk_gpio_softc*) ; 
 int /*<<< orphan*/  MTK_GPIO_LOCK (struct mtk_gpio_softc*) ; 
 int /*<<< orphan*/  MTK_GPIO_UNLOCK (struct mtk_gpio_softc*) ; 
 size_t MTK_READ_4 (struct mtk_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_WRITE_4 (struct mtk_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 struct mtk_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_gpio_pin_toggle(device_t dev, uint32_t pin)
{
	struct mtk_gpio_softc *sc;
	uint32_t val;
	int ret;

	sc = device_get_softc(dev);
	ret = 0;

	if (pin >= sc->num_pins)
		return (EINVAL);

	MTK_GPIO_LOCK(sc);
	if(!(sc->pins[pin].pin_flags & GPIO_PIN_OUTPUT)) {
		ret = EINVAL;
		goto out;
	}
	val = MTK_READ_4(sc, GPIO_PIODATA(sc));
	val &= (1u << pin);
	if (val)
		MTK_WRITE_4(sc, GPIO_PIORESET(sc), (1u << pin));
	else
		MTK_WRITE_4(sc, GPIO_PIOSET(sc), (1u << pin));

out:
	MTK_GPIO_UNLOCK(sc);

	return (ret);
}