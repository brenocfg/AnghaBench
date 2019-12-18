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
struct pad_softc {struct gpio_bank* gpio_map; } ;
struct gpio_bank {int ngpio; } ;

/* Variables and functions */

__attribute__((used)) static int
get_bank(struct pad_softc *sc, int gpio_number,
    struct gpio_bank *bank, int *pin_shift)
{
	int ngpio;
	int i;
	int n;

	n = 0;
	for (i = 0; sc->gpio_map[i].ngpio != -1; i++) {
		ngpio = sc->gpio_map[i].ngpio;

		if ((n + ngpio) > gpio_number) {
			*bank = sc->gpio_map[i];
			*pin_shift = (gpio_number - n);
			return (0);
		}

		n += ngpio;
	}

	return (-1);
}