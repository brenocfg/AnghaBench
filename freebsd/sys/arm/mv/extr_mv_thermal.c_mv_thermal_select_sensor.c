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
typedef  int uint32_t ;
struct mv_thermal_softc {int cur_sensor; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL0 ; 
 int CONTROL0_CHANNEL_MASK ; 
 int CONTROL0_CHANNEL_SHIFT ; 
 int CONTROL0_MODE_EXTERNAL ; 
 int CONTROL0_MODE_MASK ; 
 int CONTROL0_MODE_SHIFT ; 
 int CONTROL0_TSEN_EN ; 
 int CONTROL0_TSEN_START ; 
 int RD4 (struct mv_thermal_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct mv_thermal_softc*,int /*<<< orphan*/ ,int) ; 
 int mv_thermal_wait_sensor (struct mv_thermal_softc*) ; 

__attribute__((used)) static int
mv_thermal_select_sensor(struct mv_thermal_softc *sc, int sensor)
{
	uint32_t reg;

	if (sc->cur_sensor == sensor)
		return (0);

	/* Stop the current reading and reset the module */
	reg = RD4(sc, CONTROL0);
	reg &= ~(CONTROL0_TSEN_START | CONTROL0_TSEN_EN);
	WR4(sc, CONTROL0, reg);

	/* Switch to the selected sensor */
	/*
	 * NOTE : Datasheet says to use CONTROL1 for selecting
	 * but when doing so the sensors >0 are never ready
	 * Do what Linux does using undocumented bits in CONTROL0
	 */
	/* This reset automatically to the sensor 0 */
	reg &= ~(CONTROL0_MODE_MASK << CONTROL0_MODE_SHIFT);
	if (sensor) {
		/* Select external sensor */
		reg |= CONTROL0_MODE_EXTERNAL << CONTROL0_MODE_SHIFT;
		reg &= ~(CONTROL0_CHANNEL_MASK << CONTROL0_CHANNEL_SHIFT);
		reg |= (sensor - 1) << CONTROL0_CHANNEL_SHIFT;
	}
	WR4(sc, CONTROL0, reg);
	sc->cur_sensor = sensor;

	/* Start the reading */
	reg = RD4(sc, CONTROL0);
	reg |= CONTROL0_TSEN_START | CONTROL0_TSEN_EN;
	WR4(sc, CONTROL0, reg);

	return (mv_thermal_wait_sensor(sc));
}