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
typedef  int /*<<< orphan*/  uint32_t ;
struct aw_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AW_GPIO_LOCK (struct aw_gpio_softc*) ; 
 int /*<<< orphan*/  AW_GPIO_UNLOCK (struct aw_gpio_softc*) ; 
 int aw_gpio_pin_set_locked (struct aw_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 struct aw_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_gpio_pin_set(device_t dev, uint32_t pin, unsigned int value)
{
	struct aw_gpio_softc *sc;
	int ret;

	sc = device_get_softc(dev);

	AW_GPIO_LOCK(sc);
	ret = aw_gpio_pin_set_locked(sc, pin, value);
	AW_GPIO_UNLOCK(sc);

	return (ret);
}