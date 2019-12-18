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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int chip_id; } ;
struct bhnd_pmu_softc {TYPE_1__ cid; int /*<<< orphan*/  chipc_dev; } ;

/* Variables and functions */
 int BHND_CHIPC_READ_CHIPST (int /*<<< orphan*/ ) ; 
#define  BHND_CHIPID_BCM4312 144 
#define  BHND_CHIPID_BCM4325 143 
#define  BHND_CHIPID_BCM4328 142 
#define  BHND_CHIPID_BCM4330 141 
#define  BHND_CHIPID_BCM4331 140 
#define  BHND_CHIPID_BCM4336 139 
#define  BHND_CHIPID_BCM5354 138 
 int /*<<< orphan*/  BHND_PMU_GET_BITS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_REGCTRL_WRITE (struct bhnd_pmu_softc*,int,int,int) ; 
 int /*<<< orphan*/  CHIPC_CST4325_PMUTOP_2B ; 
 int ENODEV ; 
 int /*<<< orphan*/  PMU_LOG (struct bhnd_pmu_softc*,char*,int) ; 
#define  SET_LDO_VOLTAGE_CBUCK_BURST 137 
#define  SET_LDO_VOLTAGE_CBUCK_PWM 136 
#define  SET_LDO_VOLTAGE_CLDO_BURST 135 
#define  SET_LDO_VOLTAGE_CLDO_PWM 134 
#define  SET_LDO_VOLTAGE_LDO1 133 
#define  SET_LDO_VOLTAGE_LDO2 132 
#define  SET_LDO_VOLTAGE_LDO3 131 
#define  SET_LDO_VOLTAGE_LNLDO1 130 
#define  SET_LDO_VOLTAGE_LNLDO2_SEL 129 
#define  SET_LDO_VOLTAGE_PAREF 128 

int
bhnd_pmu_set_ldo_voltage(struct bhnd_pmu_softc *sc, uint8_t ldo,
    uint8_t voltage)
{
	uint32_t	chipst;
	uint32_t	regctrl;
	uint8_t		shift;
	uint8_t		mask;
	uint8_t		addr;

	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4328:
	case BHND_CHIPID_BCM5354:
		switch (ldo) {
		case SET_LDO_VOLTAGE_LDO1:
			addr = 2;
			shift = 17 + 8;
			mask = 0xf;
			break;
		case SET_LDO_VOLTAGE_LDO2:
			addr = 3;
			shift = 1;
			mask = 0xf;
			break;
		case SET_LDO_VOLTAGE_LDO3:
			addr = 3;
			shift = 9;
			mask = 0xf;
			break;
		case SET_LDO_VOLTAGE_PAREF:
			addr = 3;
			shift = 17;
			mask = 0x3f;
			break;
		default:
			PMU_LOG(sc, "unknown BCM4328/BCM5354 LDO %hhu\n", ldo);
			return (ENODEV);
		}
		break;
	case BHND_CHIPID_BCM4312:
		switch (ldo) {
		case SET_LDO_VOLTAGE_PAREF:
			addr = 0;
			shift = 21;
			mask = 0x3f;
			break;
		default:
			PMU_LOG(sc, "unknown BCM4312 LDO %hhu\n", ldo);
			return (ENODEV);
		}
		break;
	case BHND_CHIPID_BCM4325:
		switch (ldo) {
		case SET_LDO_VOLTAGE_CLDO_PWM:
			addr = 5;
			shift = 9;
			mask = 0xf;
			break;
		case SET_LDO_VOLTAGE_CLDO_BURST:
			addr = 5;
			shift = 13;
			mask = 0xf;
			break;
		case SET_LDO_VOLTAGE_CBUCK_PWM:
			addr = 3;
			shift = 20;
			mask = 0x1f;
			/* Bit 116 & 119 are inverted in CLB for opt 2b */
			chipst = BHND_CHIPC_READ_CHIPST(sc->chipc_dev);
			if (BHND_PMU_GET_BITS(chipst, CHIPC_CST4325_PMUTOP_2B))
				voltage ^= 0x9;
			break;
		case SET_LDO_VOLTAGE_CBUCK_BURST:
			addr = 3;
			shift = 25;
			mask = 0x1f;
			/* Bit 121 & 124 are inverted in CLB for opt 2b */
			chipst = BHND_CHIPC_READ_CHIPST(sc->chipc_dev);
			if (BHND_PMU_GET_BITS(chipst, CHIPC_CST4325_PMUTOP_2B))
				voltage ^= 0x9;
			break;
		case SET_LDO_VOLTAGE_LNLDO1:
			addr = 5;
			shift = 17;
			mask = 0x1f;
			break;
		case SET_LDO_VOLTAGE_LNLDO2_SEL:
			addr = 6;
			shift = 0;
			mask = 0x1;
			break;
		default:
			PMU_LOG(sc, "unknown BCM4325 LDO %hhu\n", ldo);
			return (ENODEV);
		}
		break;
	case BHND_CHIPID_BCM4336:
		switch (ldo) {
		case SET_LDO_VOLTAGE_CLDO_PWM:
			addr = 4;
			shift = 1;
			mask = 0xf;
			break;
		case SET_LDO_VOLTAGE_CLDO_BURST:
			addr = 4;
			shift = 5;
			mask = 0xf;
			break;
		case SET_LDO_VOLTAGE_LNLDO1:
			addr = 4;
			shift = 17;
			mask = 0xf;
			break;
		default:
			PMU_LOG(sc, "unknown BCM4336 LDO %hhu\n", ldo);
			return (ENODEV);
		}
		break;
	case BHND_CHIPID_BCM4330:
		switch (ldo) {
		case SET_LDO_VOLTAGE_CBUCK_PWM:
			addr = 3;
			shift = 0;
			mask = 0x1f;
			break;
		default:
			PMU_LOG(sc, "unknown BCM4330 LDO %hhu\n", ldo);
			return (ENODEV);
		}
		break;
	case BHND_CHIPID_BCM4331:
		switch (ldo) {
		case  SET_LDO_VOLTAGE_PAREF:
			addr = 1;
			shift = 0;
			mask = 0xf;
			break;
		default:
			PMU_LOG(sc, "unknown BCM4331 LDO %hhu\n", ldo);
			return (ENODEV);
		}
		break;
	default:
		PMU_LOG(sc, "cannot set LDO voltage on unsupported chip %hu\n",
		    sc->cid.chip_id);
		return (ENODEV);
	}

	regctrl = (voltage & mask) << shift;
	BHND_PMU_REGCTRL_WRITE(sc, addr, regctrl, mask << shift);

	return (0);
}