#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mv_thermal_softc {TYPE_1__* config; } ;
struct TYPE_2__ {int valid_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int RD4 (struct mv_thermal_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS ; 

__attribute__((used)) static int
mv_thermal_wait_sensor(struct mv_thermal_softc *sc)
{
	uint32_t reg;
	uint32_t timeout;

	timeout = 100000;
	while (--timeout > 0) {
		reg = RD4(sc, STATUS);
		if ((reg & sc->config->valid_mask) == sc->config->valid_mask)
			break;
		DELAY(100);
	}
	if (timeout == 0) {
		return (ETIMEDOUT);
	}

	return (0);
}