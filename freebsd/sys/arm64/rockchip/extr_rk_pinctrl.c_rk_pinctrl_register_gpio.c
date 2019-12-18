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
struct rk_pinctrl_softc {TYPE_1__* conf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  gpio_dev; int /*<<< orphan*/  gpio_name; } ;
struct TYPE_3__ {int ngpio_bank; TYPE_2__* gpio_bank; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rk_pinctrl_register_gpio(struct rk_pinctrl_softc *sc, char *gpio_name,
    device_t gpio_dev)
{
	int i;

	for(i = 0; i < sc->conf->ngpio_bank; i++) {
		if (strcmp(gpio_name, sc->conf->gpio_bank[i].gpio_name) != 0)
			continue;
		sc->conf->gpio_bank[i].gpio_dev = gpio_dev;
		return(0);
	}
	return (ENXIO);
}