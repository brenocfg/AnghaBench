#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct aw_gpio_softc {TYPE_2__* padconf; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  scalar_t__ pcell_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int npins; TYPE_1__* pins; } ;
struct TYPE_3__ {scalar_t__ port; scalar_t__ pin; } ;

/* Variables and functions */
 struct aw_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_gpio_map_gpios(device_t bus, phandle_t dev, phandle_t gparent, int gcells,
    pcell_t *gpios, uint32_t *pin, uint32_t *flags)
{
	struct aw_gpio_softc *sc;
	int i;

	sc = device_get_softc(bus);

	/* The GPIO pins are mapped as: <gpio-phandle bank pin flags>. */
	for (i = 0; i < sc->padconf->npins; i++)
		if (sc->padconf->pins[i].port == gpios[0] &&
		    sc->padconf->pins[i].pin == gpios[1]) {
			*pin = i;
			break;
		}
	*flags = gpios[gcells - 1];

	return (0);
}