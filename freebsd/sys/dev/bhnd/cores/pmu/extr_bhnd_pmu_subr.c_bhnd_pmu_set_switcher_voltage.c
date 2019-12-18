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
typedef  int uint8_t ;
struct bhnd_pmu_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PMU_REGCTRL_WRITE (struct bhnd_pmu_softc*,int,int,int /*<<< orphan*/ ) ; 

void
bhnd_pmu_set_switcher_voltage(struct bhnd_pmu_softc *sc, uint8_t bb_voltage,
    uint8_t rf_voltage)
{
	BHND_PMU_REGCTRL_WRITE(sc, 0x01, (bb_voltage & 0x1f) << 22, ~0);
	BHND_PMU_REGCTRL_WRITE(sc, 0x00, (rf_voltage & 0x1f) << 14, ~0);
}