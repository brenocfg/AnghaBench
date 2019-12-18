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
struct aml8726_gpio_softc {scalar_t__ npins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIOMAXNAME ; 
 struct aml8726_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 

__attribute__((used)) static int
aml8726_gpio_pin_getname(device_t dev, uint32_t pin, char *name)
{
	struct aml8726_gpio_softc *sc = device_get_softc(dev);

	if (pin >= sc->npins)
		return (EINVAL);

	snprintf(name, GPIOMAXNAME, "%s.%u", ofw_bus_get_name(dev), pin);

	return (0);
}