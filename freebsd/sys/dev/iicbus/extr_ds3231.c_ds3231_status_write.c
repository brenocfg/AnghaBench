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
typedef  int /*<<< orphan*/  uint8_t ;
struct ds3231_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS3231_STATUS ; 
 int /*<<< orphan*/  DS3231_STATUS_A1F ; 
 int /*<<< orphan*/  DS3231_STATUS_A2F ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ds3231_write1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds3231_status_write(struct ds3231_softc *sc, int clear_a1, int clear_a2)
{
	int error;
	uint8_t data;

	data = sc->sc_status;
	if (clear_a1 == 0)
		data |= DS3231_STATUS_A1F;
	if (clear_a2 == 0)
		data |= DS3231_STATUS_A2F;
	error = ds3231_write1(sc->sc_dev, DS3231_STATUS, data);
	if (error != 0)
		device_printf(sc->sc_dev, "cannot write to RTC.\n");

	return (error);
}