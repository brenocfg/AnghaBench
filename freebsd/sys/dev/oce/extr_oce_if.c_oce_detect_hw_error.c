#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; scalar_t__ hw_error; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 scalar_t__ IS_XE201 (TYPE_1__*) ; 
 int OCE_READ_REG32 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCICFG_UE_STATUS_HIGH ; 
 int /*<<< orphan*/  PCICFG_UE_STATUS_HI_MASK ; 
 int /*<<< orphan*/  PCICFG_UE_STATUS_LOW ; 
 int /*<<< orphan*/  PCICFG_UE_STATUS_LOW_MASK ; 
 int /*<<< orphan*/  SLIPORT_ERROR1_OFFSET ; 
 int /*<<< orphan*/  SLIPORT_ERROR2_OFFSET ; 
 int SLIPORT_STATUS_ERR_MASK ; 
 int /*<<< orphan*/  SLIPORT_STATUS_OFFSET ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  db ; 
 int /*<<< orphan*/  devcfg ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int* ue_status_hi_desc ; 
 int* ue_status_low_desc ; 

__attribute__((used)) static void oce_detect_hw_error(POCE_SOFTC sc)
{

	uint32_t ue_low = 0, ue_high = 0, ue_low_mask = 0, ue_high_mask = 0;
	uint32_t sliport_status = 0, sliport_err1 = 0, sliport_err2 = 0;
	uint32_t i;

	if (sc->hw_error)
		return;

	if (IS_XE201(sc)) {
		sliport_status = OCE_READ_REG32(sc, db, SLIPORT_STATUS_OFFSET);
		if (sliport_status & SLIPORT_STATUS_ERR_MASK) {
			sliport_err1 = OCE_READ_REG32(sc, db, SLIPORT_ERROR1_OFFSET);
			sliport_err2 = OCE_READ_REG32(sc, db, SLIPORT_ERROR2_OFFSET);
		}
	} else {
		ue_low = OCE_READ_REG32(sc, devcfg, PCICFG_UE_STATUS_LOW);
		ue_high = OCE_READ_REG32(sc, devcfg, PCICFG_UE_STATUS_HIGH);
		ue_low_mask = OCE_READ_REG32(sc, devcfg, PCICFG_UE_STATUS_LOW_MASK);
		ue_high_mask = OCE_READ_REG32(sc, devcfg, PCICFG_UE_STATUS_HI_MASK);

		ue_low = (ue_low & ~ue_low_mask);
		ue_high = (ue_high & ~ue_high_mask);
	}

	/* On certain platforms BE hardware can indicate spurious UEs.
	 * Allow the h/w to stop working completely in case of a real UE.
	 * Hence not setting the hw_error for UE detection.
	 */
	if (sliport_status & SLIPORT_STATUS_ERR_MASK) {
		sc->hw_error = TRUE;
		device_printf(sc->dev, "Error detected in the card\n");
	}

	if (sliport_status & SLIPORT_STATUS_ERR_MASK) {
		device_printf(sc->dev,
				"ERR: sliport status 0x%x\n", sliport_status);
		device_printf(sc->dev,
				"ERR: sliport error1 0x%x\n", sliport_err1);
		device_printf(sc->dev,
				"ERR: sliport error2 0x%x\n", sliport_err2);
	}

	if (ue_low) {
		for (i = 0; ue_low; ue_low >>= 1, i++) {
			if (ue_low & 1)
				device_printf(sc->dev, "UE: %s bit set\n",
							ue_status_low_desc[i]);
		}
	}

	if (ue_high) {
		for (i = 0; ue_high; ue_high >>= 1, i++) {
			if (ue_high & 1)
				device_printf(sc->dev, "UE: %s bit set\n",
							ue_status_hi_desc[i]);
		}
	}

}