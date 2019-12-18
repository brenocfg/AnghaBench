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
struct zy7_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int RD4 (struct zy7_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_PIN (int) ; 
 int /*<<< orphan*/  ZY7_GPIO_DATA_RO (int) ; 
 struct zy7_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zy7_gpio_pin_get(device_t dev, uint32_t pin, unsigned int *value)
{
	struct zy7_gpio_softc *sc = device_get_softc(dev);

	if (!VALID_PIN(pin))
		return (EINVAL);

	*value = (RD4(sc, ZY7_GPIO_DATA_RO(pin >> 5)) >> (pin & 31)) & 1;

	return (0);
}