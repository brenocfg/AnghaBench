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
struct ds1775_softc {int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS1775_TEMP ; 
 int ZERO_C_TO_K ; 
 int ds1775_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
ds1775_sensor_read(struct ds1775_softc *sc)
{
	uint16_t buf[2];
	uint16_t read;
	int err;

	err = ds1775_read_2(sc->sc_dev, sc->sc_addr, DS1775_TEMP, buf);
	if (err < 0)
		return (-1);

	read = *((int16_t *)buf);

	/* The default mode of the ADC is 9 bit, the resolution is 0.5 C per
	   bit. The temperature is in tenth kelvin.
	*/
	return (((int16_t)(read) >> 7) * 5 + ZERO_C_TO_K);
}