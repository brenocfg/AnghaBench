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
struct aw_gpio_softc {TYPE_1__* padconf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int npins; } ;

/* Variables and functions */
 struct aw_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_gpio_pin_max(device_t dev, int *maxpin)
{
	struct aw_gpio_softc *sc;

	sc = device_get_softc(dev);

	*maxpin = sc->padconf->npins - 1;
	return (0);
}