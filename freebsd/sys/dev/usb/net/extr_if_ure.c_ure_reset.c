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
struct TYPE_2__ {int /*<<< orphan*/  ue_dev; } ;
struct ure_softc {TYPE_1__ sc_ue; } ;

/* Variables and functions */
 int URE_CR_RST ; 
 int /*<<< orphan*/  URE_MCU_TYPE_PLA ; 
 int /*<<< orphan*/  URE_PLA_CR ; 
 int URE_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  uether_pause (TYPE_1__*,int) ; 
 int ure_read_1 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ure_write_1 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ure_reset(struct ure_softc *sc)
{
	int i;

	ure_write_1(sc, URE_PLA_CR, URE_MCU_TYPE_PLA, URE_CR_RST);

	for (i = 0; i < URE_TIMEOUT; i++) {
		if (!(ure_read_1(sc, URE_PLA_CR, URE_MCU_TYPE_PLA) &
		    URE_CR_RST))
			break;
		uether_pause(&sc->sc_ue, hz / 100);
	}
	if (i == URE_TIMEOUT)
		device_printf(sc->sc_ue.ue_dev, "reset never completed\n");
}