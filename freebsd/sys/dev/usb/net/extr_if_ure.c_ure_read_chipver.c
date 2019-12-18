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
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  ue_dev; } ;
struct ure_softc {TYPE_1__ sc_ue; int /*<<< orphan*/  sc_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  URE_CHIP_VER_4C00 ; 
 int /*<<< orphan*/  URE_CHIP_VER_4C10 ; 
 int /*<<< orphan*/  URE_CHIP_VER_5C00 ; 
 int /*<<< orphan*/  URE_CHIP_VER_5C10 ; 
 int /*<<< orphan*/  URE_CHIP_VER_5C20 ; 
 int /*<<< orphan*/  URE_CHIP_VER_5C30 ; 
 int /*<<< orphan*/  URE_MCU_TYPE_PLA ; 
 int /*<<< orphan*/  URE_PLA_TCR1 ; 
 int URE_VERSION_MASK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int ure_read_2 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ure_read_chipver(struct ure_softc *sc)
{
	uint16_t ver;

	ver = ure_read_2(sc, URE_PLA_TCR1, URE_MCU_TYPE_PLA) & URE_VERSION_MASK;
	switch (ver) {
	case 0x4c00:
		sc->sc_chip |= URE_CHIP_VER_4C00;
		break;
	case 0x4c10:
		sc->sc_chip |= URE_CHIP_VER_4C10;
		break;
	case 0x5c00:
		sc->sc_chip |= URE_CHIP_VER_5C00;
		break;
	case 0x5c10:
		sc->sc_chip |= URE_CHIP_VER_5C10;
		break;
	case 0x5c20:
		sc->sc_chip |= URE_CHIP_VER_5C20;
		break;
	case 0x5c30:
		sc->sc_chip |= URE_CHIP_VER_5C30;
		break;
	default:
		device_printf(sc->sc_ue.ue_dev,
		    "unknown version 0x%04x\n", ver);
		break;
	}
}