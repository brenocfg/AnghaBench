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
typedef  scalar_t__ uint32_t ;
struct mv_gpio_softc {scalar_t__ pin_num; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MV_GPIO_LOCK () ; 
 int /*<<< orphan*/  MV_GPIO_UNLOCK () ; 
 struct mv_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_gpio_value_set (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static int
mv_gpio_pin_set(device_t dev, uint32_t pin, unsigned int value)
{
	struct mv_gpio_softc *sc = device_get_softc(dev);
	if (pin >= sc->pin_num)
		return (EINVAL);

	MV_GPIO_LOCK();
	mv_gpio_value_set(dev, pin, value);
	MV_GPIO_UNLOCK();

	return (0);
}