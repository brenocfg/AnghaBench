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
typedef  int uint16_t ;
struct ds1631_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  init_done; } ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS1631_TEMP ; 
 int ZERO_C_TO_K ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ds1631_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ds1631_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
ds1631_sensor_read(struct ds1631_softc *sc)
{
	uint16_t buf[2];
	uint16_t read;
	int err;

	if (!sc->init_done)
		ds1631_init(sc->sc_dev, sc->sc_addr);

	err = ds1631_read_2(sc->sc_dev, sc->sc_addr, DS1631_TEMP, buf);
	if (err < 0) {
		device_printf(sc->sc_dev, "ds1631 read TEMP failed: %x\n", err);
		return (-1);
	}

	read = *((int16_t *)buf);

	/*
	 * The default mode of the ADC is 12-bit, the resolution is 0.0625 C
	 * per bit. The temperature is in tenth kelvin.
	 * We use 10-bit resolution which seems enough, resolution is 0.25 C.
	 */

	return (((int16_t)(read) >> 6) * 25 / 10 + ZERO_C_TO_K);
}