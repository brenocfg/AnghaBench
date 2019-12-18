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
struct armada_thermal_softc {int /*<<< orphan*/  ctrl_res; } ;

/* Variables and functions */
 int A380_TSEN_CTRL_RESET ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
armada380_tsen_init(struct armada_thermal_softc *sc)
{
	uint32_t tsen_ctrl;

	tsen_ctrl = bus_read_4(sc->ctrl_res, 0);
	if ((tsen_ctrl & A380_TSEN_CTRL_RESET) == 0) {
		tsen_ctrl |= A380_TSEN_CTRL_RESET;
		bus_write_4(sc->ctrl_res, 0, tsen_ctrl);
		DELAY(10000);
	}
}