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
struct ds3231_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS3231_CONTROL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ds3231_read1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ds3231_ctrl_read(struct ds3231_softc *sc)
{
	int error;

	error = ds3231_read1(sc->sc_dev, DS3231_CONTROL, &sc->sc_ctrl);
	if (error) {
		device_printf(sc->sc_dev, "cannot read from RTC.\n");
		return (error);
	}
	return (0);
}