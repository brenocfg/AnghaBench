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
struct mv_gpio_softc {int pin_num; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 struct mv_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_gpio_pin_max(device_t dev, int *maxpin)
{
	struct mv_gpio_softc *sc;
	if (maxpin == NULL)
		return (EINVAL);

	sc = device_get_softc(dev);
	*maxpin = sc->pin_num;

	return (0);
}