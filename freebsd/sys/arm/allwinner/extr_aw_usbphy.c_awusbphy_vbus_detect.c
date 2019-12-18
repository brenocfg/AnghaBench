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
struct awusbphy_softc {int /*<<< orphan*/  vbus_det_pin; scalar_t__ vbus_det_valid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct awusbphy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int gpio_pin_is_active (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
awusbphy_vbus_detect(device_t dev, int *val)
{
	struct awusbphy_softc *sc;
	bool active;
	int error;

	sc = device_get_softc(dev);

	if (sc->vbus_det_valid) {
		error = gpio_pin_is_active(sc->vbus_det_pin, &active);
		if (error != 0) {
			device_printf(dev, "Cannot get status of id pin %d\n",
			    error);
			return (error);
		}
		*val = active;
		return (0);
	}

	*val = 0;
	return (0);
}