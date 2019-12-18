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
struct mv_thermal_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL0 ; 
 int CONTROL0_OSR_MAX ; 
 int CONTROL0_OSR_SHIFT ; 
 int CONTROL0_TSEN_EN ; 
 int CONTROL0_TSEN_RESET ; 
 int CONTROL0_TSEN_START ; 
 int RD4 (struct mv_thermal_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct mv_thermal_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_thermal_wait_sensor (struct mv_thermal_softc*) ; 

__attribute__((used)) static int
ap806_init(struct mv_thermal_softc *sc)
{
	uint32_t reg;

	/* Start the temp capture/conversion */
	reg = RD4(sc, CONTROL0);
	reg &= ~CONTROL0_TSEN_RESET;
	reg |= CONTROL0_TSEN_START | CONTROL0_TSEN_EN;

	/* Sample every ~2ms */
	reg |= CONTROL0_OSR_MAX << CONTROL0_OSR_SHIFT;

	WR4(sc, CONTROL0, reg);

	/* Since we just started the module wait for the sensor to be ready */
	mv_thermal_wait_sensor(sc);

	return (0);
}