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
struct rt1310_gpio_softc {int dummy; } ;
struct rt1310_gpio_pinmap {int lp_port; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int GPIO_PIN_OUTPUT ; 
 int RT_GPIO_OFF_PADR ; 
 int RT_GPIO_OFF_PBDR ; 
 int RT_GPIO_PIN_BIT (struct rt1310_gpio_pinmap const*,int) ; 
#define  RT_GPIO_PORTA 129 
#define  RT_GPIO_PORTB 128 
 struct rt1310_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct rt1310_gpio_pinmap* rt1310_gpio_get_pinmap (int) ; 
 scalar_t__ rt1310_gpio_pin_getflags (int /*<<< orphan*/ ,int,int*) ; 
 int rt1310_gpio_read_4 (struct rt1310_gpio_softc*,int) ; 
 int /*<<< orphan*/  rt1310_gpio_write_4 (struct rt1310_gpio_softc*,int,int) ; 

__attribute__((used)) static int
rt1310_gpio_pin_set(device_t dev, uint32_t pin, uint32_t value)
{
	struct rt1310_gpio_softc *sc = device_get_softc(dev);
	const struct rt1310_gpio_pinmap *map;
	uint32_t state, flags;
	uint32_t port;

	map = rt1310_gpio_get_pinmap(pin);

	if (rt1310_gpio_pin_getflags(dev, pin, &flags))
		return (ENXIO);

	if ((flags & GPIO_PIN_OUTPUT) == 0)
		return (EINVAL);

	switch (map->lp_port) {
	case RT_GPIO_PORTA:
		port = RT_GPIO_OFF_PADR;
		break;
	case RT_GPIO_PORTB:
		port = RT_GPIO_OFF_PBDR;
		break;
	}

	state = rt1310_gpio_read_4(sc, port);
	if (value == 1) {
		state |= (1 << RT_GPIO_PIN_BIT(map, pin));
	} else {
		state &= ~(1 << RT_GPIO_PIN_BIT(map, pin));
	}
	rt1310_gpio_write_4(sc, port, state);

	return (0);
}