#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int chip_id; } ;
struct bhnd_pmu_softc {int /*<<< orphan*/  chipc_dev; TYPE_1__ cid; } ;
struct TYPE_4__ {int /*<<< orphan*/  chipstatus; } ;

/* Variables and functions */
 int BHND_CHIPC_READ_CHIPST (int /*<<< orphan*/ ) ; 
#define  BHND_CHIPID_BCM4325 129 
#define  BHND_CHIPID_BCM4329 128 
 int /*<<< orphan*/  BHND_PMU_AND_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BHND_PMU_CHIP_CONTROL_ADDR ; 
 int /*<<< orphan*/  BHND_PMU_CHIP_CONTROL_DATA ; 
 int /*<<< orphan*/  BHND_PMU_GET_BITS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_OR_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int) ; 
 int BHND_PMU_READ_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_REG_CONTROL_ADDR ; 
 int /*<<< orphan*/  BHND_PMU_REG_CONTROL_DATA ; 
 int /*<<< orphan*/  BHND_PMU_WRITE_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CHIPC_CST4325_RCAL_VALID ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PMU_DEBUG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  R_REG (int /*<<< orphan*/ *) ; 
 TYPE_2__* cc ; 

void 
bhnd_pmu_rcal(struct bhnd_pmu_softc *sc)
{
	uint32_t	chipst;
	uint32_t	val;
	uint8_t		rcal_code;
	bool		bluetooth_rcal;


	bluetooth_rcal = false;

	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4325:
	case BHND_CHIPID_BCM4329:
		/* Kick RCal */
		BHND_PMU_WRITE_4(sc, BHND_PMU_CHIP_CONTROL_ADDR, 1);

		/* Power Down RCAL Block */
		BHND_PMU_AND_4(sc, BHND_PMU_CHIP_CONTROL_DATA, ~0x04);

		if (sc->cid.chip_id == BHND_CHIPID_BCM4325) {
			chipst = BHND_CHIPC_READ_CHIPST(sc->chipc_dev);
			if (BHND_PMU_GET_BITS(chipst, CHIPC_CST4325_RCAL_VALID))
				bluetooth_rcal = true;
		}

		/* Power Up RCAL block */
		BHND_PMU_AND_4(sc, BHND_PMU_CHIP_CONTROL_DATA, 0x04);

		/* Wait for completion */
		for (int i = 0; i < (10 * 1000 * 1000); i++) {
			chipst = BHND_CHIPC_READ_CHIPST(sc->chipc_dev);

			if (chipst & 0x08)
				break;

			DELAY(10);
		}
		KASSERT((chipst & 0x08) != 0, ("rcal completion timeout"));

		if (bluetooth_rcal) {
			rcal_code = 0x6;
		} else {
			/* Drop LSB to convert from 5 bit code to 4 bit code */
			rcal_code = (uint8_t) (chipst >> 5) & 0x0f;
		}

		PMU_DEBUG("RCal completed, status 0x%x, code 0x%x\n",
		    R_REG(&cc->chipstatus), rcal_code);

		/* Write RCal code into pmu_vreg_ctrl[32:29] */
		BHND_PMU_WRITE_4(sc, BHND_PMU_REG_CONTROL_ADDR, 0);
		val = BHND_PMU_READ_4(sc, BHND_PMU_REG_CONTROL_DATA);
		val &= ~((uint32_t) 0x07 << 29);
		val |= (uint32_t) (rcal_code & 0x07) << 29;
		BHND_PMU_WRITE_4(sc, BHND_PMU_REG_CONTROL_DATA, val);

		BHND_PMU_WRITE_4(sc, BHND_PMU_REG_CONTROL_ADDR, 1);
		val = BHND_PMU_READ_4(sc, BHND_PMU_REG_CONTROL_DATA);
		val &= ~(uint32_t) 0x01;
		val |= (uint32_t) ((rcal_code >> 3) & 0x01);
		BHND_PMU_WRITE_4(sc, BHND_PMU_REG_CONTROL_DATA, val);

		/* Write RCal code into pmu_chip_ctrl[33:30] */
		BHND_PMU_WRITE_4(sc, BHND_PMU_CHIP_CONTROL_ADDR, 0);
		val = BHND_PMU_READ_4(sc, BHND_PMU_CHIP_CONTROL_DATA);
		val &= ~((uint32_t) 0x03 << 30);
		val |= (uint32_t) (rcal_code & 0x03) << 30;
		BHND_PMU_WRITE_4(sc, BHND_PMU_CHIP_CONTROL_DATA, val);

		BHND_PMU_WRITE_4(sc, BHND_PMU_CHIP_CONTROL_ADDR, 1);
		val = BHND_PMU_READ_4(sc, BHND_PMU_CHIP_CONTROL_DATA);
		val &= ~(uint32_t) 0x03;
		val |= (uint32_t) ((rcal_code >> 2) & 0x03);
		BHND_PMU_WRITE_4(sc, BHND_PMU_CHIP_CONTROL_DATA, val);

		/* Set override in pmu_chip_ctrl[29] */
		BHND_PMU_WRITE_4(sc, BHND_PMU_CHIP_CONTROL_ADDR, 0);
		BHND_PMU_OR_4(sc, BHND_PMU_CHIP_CONTROL_DATA, (0x01 << 29));

		/* Power off RCal block */
		BHND_PMU_WRITE_4(sc, BHND_PMU_CHIP_CONTROL_ADDR, 1);
		BHND_PMU_AND_4(sc, BHND_PMU_CHIP_CONTROL_DATA, ~0x04);
		break;
	default:
		break;
	}
}