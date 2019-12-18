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
 int /*<<< orphan*/  CONTROL1 ; 
 int RD4 (struct mv_thermal_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct mv_thermal_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cp110_init(struct mv_thermal_softc *sc)
{
	uint32_t reg;

	reg = RD4(sc, CONTROL1);
	reg &= (1 << 7);
	reg |= (1 << 8);
	WR4(sc, CONTROL1, reg);

	/* Sample every ~2ms */
	reg = RD4(sc, CONTROL0);
	reg |= CONTROL0_OSR_MAX << CONTROL0_OSR_SHIFT;
	WR4(sc, CONTROL0, reg);

	return (0);
}