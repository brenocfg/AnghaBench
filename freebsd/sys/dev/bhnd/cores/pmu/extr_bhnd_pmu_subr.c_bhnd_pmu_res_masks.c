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
struct TYPE_4__ {int chip_id; int chip_rev; } ;
struct TYPE_3__ {int board_flags; int /*<<< orphan*/  board_type; } ;
struct bhnd_pmu_softc {int caps; int /*<<< orphan*/  chipc_dev; TYPE_2__ cid; TYPE_1__ board; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_ATTACH_NATIVE ; 
 int BHND_BFL_BUCKBOOST ; 
#define  BHND_BOARD_BCM94325BGABU 158 
#define  BHND_BOARD_BCM94325DEVBU 157 
 int BHND_CHIPC_READ_CHIPST (int /*<<< orphan*/ ) ; 
#define  BHND_CHIPID_BCM43111 156 
#define  BHND_CHIPID_BCM43112 155 
#define  BHND_CHIPID_BCM4312 154 
#define  BHND_CHIPID_BCM4313 153 
#define  BHND_CHIPID_BCM4319 152 
#define  BHND_CHIPID_BCM4322 151 
#define  BHND_CHIPID_BCM43221 150 
#define  BHND_CHIPID_BCM43222 149 
#define  BHND_CHIPID_BCM43224 148 
#define  BHND_CHIPID_BCM43225 147 
#define  BHND_CHIPID_BCM43226 146 
#define  BHND_CHIPID_BCM43231 145 
#define  BHND_CHIPID_BCM43234 144 
#define  BHND_CHIPID_BCM43235 143 
#define  BHND_CHIPID_BCM43236 142 
#define  BHND_CHIPID_BCM43237 141 
#define  BHND_CHIPID_BCM43238 140 
#define  BHND_CHIPID_BCM4325 139 
#define  BHND_CHIPID_BCM4328 138 
#define  BHND_CHIPID_BCM4329 137 
#define  BHND_CHIPID_BCM4330 136 
#define  BHND_CHIPID_BCM4331 135 
#define  BHND_CHIPID_BCM4336 134 
#define  BHND_CHIPID_BCM4342 133 
#define  BHND_CHIPID_BCM43420 132 
#define  BHND_CHIPID_BCM43421 131 
#define  BHND_CHIPID_BCM43431 130 
#define  BHND_CHIPID_BCM5354 129 
#define  BHND_CHIPID_BCM6362 128 
 int /*<<< orphan*/  BHND_NVAR_RMAX ; 
 int /*<<< orphan*/  BHND_NVAR_RMIN ; 
 int /*<<< orphan*/  BHND_PMU_CAP_RC ; 
 void* BHND_PMU_GET_BITS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIPC_CST4325_PMUTOP_2B ; 
 int /*<<< orphan*/  CHIPC_CST4325_SPROM_OTP_SEL ; 
 int /*<<< orphan*/  CHIPC_CST4329_SPROM_OTP_SEL ; 
 int CHIPC_CST_OTP_PWRDN ; 
 int ENOENT ; 
 int PMURES_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMU_DEBUG (struct bhnd_pmu_softc*,char*,int) ; 
 int /*<<< orphan*/  PMU_LOG (struct bhnd_pmu_softc*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RES4313_ALP_AVAIL_RSRC ; 
 int /*<<< orphan*/  RES4313_BB_PLL_PWRSW_RSRC ; 
 int /*<<< orphan*/  RES4313_BB_PU_RSRC ; 
 int /*<<< orphan*/  RES4313_XTAL_PU_RSRC ; 
 int /*<<< orphan*/  RES4319_CBUCK_LPOM ; 
 int /*<<< orphan*/  RES4319_CLDO_PU ; 
 int /*<<< orphan*/  RES4322_ALP_AVAIL ; 
 int /*<<< orphan*/  RES4322_HT_PHY_AVAIL ; 
 int /*<<< orphan*/  RES4322_HT_SI_AVAIL ; 
 int /*<<< orphan*/  RES4322_OTP_PU ; 
 int /*<<< orphan*/  RES4322_PHY_PLL_ON ; 
 int /*<<< orphan*/  RES4322_RF_LDO ; 
 int /*<<< orphan*/  RES4322_SI_PLL_ON ; 
 int /*<<< orphan*/  RES4322_XTAL_PU ; 
 int /*<<< orphan*/  RES4325B0_CBUCK_LPOM ; 
 int /*<<< orphan*/  RES4325B0_CLDO_PU ; 
 int /*<<< orphan*/  RES4325_BUCK_BOOST_BURST ; 
 int /*<<< orphan*/  RES4325_OTP_PU ; 
 int /*<<< orphan*/  RES4328_BB_SWITCHER_PWM ; 
 int /*<<< orphan*/  RES4328_EXT_SWITCHER_PWM ; 
 int /*<<< orphan*/  RES4328_XTAL_EN ; 
 int /*<<< orphan*/  RES4329_CBUCK_LPOM ; 
 int /*<<< orphan*/  RES4329_CLDO_PU ; 
 int /*<<< orphan*/  RES4329_LNLDO1_PU ; 
 int /*<<< orphan*/  RES4329_OTP_PU ; 
 int /*<<< orphan*/  RES4330_CBUCK_LPOM ; 
 int /*<<< orphan*/  RES4330_CLDO_PU ; 
 int /*<<< orphan*/  RES4330_DIS_INT_RESET_PD ; 
 int /*<<< orphan*/  RES4330_LDO3P3_PU ; 
 int /*<<< orphan*/  RES4330_OTP_PU ; 
 int /*<<< orphan*/  RES4336_CBUCK_LPOM ; 
 int /*<<< orphan*/  RES4336_CLDO_PU ; 
 int /*<<< orphan*/  RES4336_DIS_INT_RESET_PD ; 
 int /*<<< orphan*/  RES4336_LDO3P3_PU ; 
 int /*<<< orphan*/  RES4336_OTP_PU ; 
 int /*<<< orphan*/  bhnd_get_attach_type (int /*<<< orphan*/ ) ; 
 int bhnd_nvram_getvar_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bhnd_pmu_res_depfltr_ncb (struct bhnd_pmu_softc*) ; 

__attribute__((used)) static int
bhnd_pmu_res_masks(struct bhnd_pmu_softc *sc, uint32_t *pmin, uint32_t *pmax)
{
	uint32_t	max_mask, min_mask;
	uint32_t	chipst, otpsel;
	uint32_t	nval;
	uint8_t		rsrcs;
	int		error;

	max_mask = 0;
	min_mask = 0;

	/* # resources */
	rsrcs = BHND_PMU_GET_BITS(sc->caps, BHND_PMU_CAP_RC);

	/* determine min/max rsrc masks */
	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4325:		
		/* If used by this device, enable the CBUCK */
		if (!bhnd_pmu_res_depfltr_ncb(sc))
			min_mask |= PMURES_BIT(RES4325B0_CBUCK_LPOM);
		
		chipst = BHND_CHIPC_READ_CHIPST(sc->chipc_dev);
		if (BHND_PMU_GET_BITS(chipst, CHIPC_CST4325_PMUTOP_2B))
			min_mask |= PMURES_BIT(RES4325B0_CLDO_PU);

		/* Is OTP required? */
		otpsel = BHND_PMU_GET_BITS(chipst, CHIPC_CST4325_SPROM_OTP_SEL);
		if (otpsel != CHIPC_CST_OTP_PWRDN)
			min_mask |= PMURES_BIT(RES4325_OTP_PU);

		/* Leave buck boost on in burst mode for certain boards */
		if (sc->board.board_flags & BHND_BFL_BUCKBOOST) {
			switch (sc->board.board_type) {
			case BHND_BOARD_BCM94325DEVBU:
			case BHND_BOARD_BCM94325BGABU:
				min_mask |= PMURES_BIT(
				    RES4325_BUCK_BOOST_BURST);
				break;
			}
		}
		
		/* Allow all resources to be turned on upon requests */
		max_mask = ~(~0 << rsrcs);
		break;

	case BHND_CHIPID_BCM4312:
		/* default min_mask = 0x80000cbb is wrong */
		min_mask = 0xcbb;
		/*
		 * max_mask = 0x7fff;
		 * pmu_res_updown_table_sz = 0;
		 * pmu_res_depend_table_sz = 0;
		 */
		break;

	case BHND_CHIPID_BCM4322:
	case BHND_CHIPID_BCM43221:
	case BHND_CHIPID_BCM43231:
	case BHND_CHIPID_BCM4342:
		if (sc->cid.chip_rev >= 2)
			break;
	
		/* request ALP(can skip for A1) */
		min_mask = PMURES_BIT(RES4322_RF_LDO) |
			   PMURES_BIT(RES4322_XTAL_PU) |
			   PMURES_BIT(RES4322_ALP_AVAIL);

		if (bhnd_get_attach_type(sc->chipc_dev) == BHND_ATTACH_NATIVE) {
			min_mask |=
			    PMURES_BIT(RES4322_SI_PLL_ON) |
			    PMURES_BIT(RES4322_HT_SI_AVAIL) |
			    PMURES_BIT(RES4322_PHY_PLL_ON) |
			    PMURES_BIT(RES4322_OTP_PU) |
			    PMURES_BIT(RES4322_HT_PHY_AVAIL);
			max_mask = 0x1ff;
		}
		break;

	case BHND_CHIPID_BCM43222:
	case BHND_CHIPID_BCM43111:
	case BHND_CHIPID_BCM43112:
	case BHND_CHIPID_BCM43224:
	case BHND_CHIPID_BCM43225:
	case BHND_CHIPID_BCM43421:
	case BHND_CHIPID_BCM43226:
	case BHND_CHIPID_BCM43420:
	case BHND_CHIPID_BCM43235:
	case BHND_CHIPID_BCM43236:
	case BHND_CHIPID_BCM43238:
	case BHND_CHIPID_BCM43234:
	case BHND_CHIPID_BCM43237:
	case BHND_CHIPID_BCM4331:
	case BHND_CHIPID_BCM43431:
	case BHND_CHIPID_BCM6362:
		/* use chip default */
		break;

	case BHND_CHIPID_BCM4328:
		min_mask =
		    PMURES_BIT(RES4328_BB_SWITCHER_PWM) |
		    PMURES_BIT(RES4328_EXT_SWITCHER_PWM) |
		    PMURES_BIT(RES4328_XTAL_EN);
		max_mask = 0xfffffff;
		break;

	case BHND_CHIPID_BCM5354:
		/* Allow (but don't require) PLL to turn on */
		max_mask = 0xfffffff;
		break;

	case BHND_CHIPID_BCM4329:
		/* Down to save the power. */
		if (sc->cid.chip_rev >= 0x2) {
			min_mask =
			    PMURES_BIT(RES4329_CBUCK_LPOM) |
			    PMURES_BIT(RES4329_LNLDO1_PU) | 
			    PMURES_BIT(RES4329_CLDO_PU);
		} else {
			min_mask =
			    PMURES_BIT(RES4329_CBUCK_LPOM) |
			    PMURES_BIT(RES4329_CLDO_PU);
		}

		/* Is OTP required? */
		chipst = BHND_CHIPC_READ_CHIPST(sc->chipc_dev);
		otpsel = BHND_PMU_GET_BITS(chipst, CHIPC_CST4329_SPROM_OTP_SEL);
		if (otpsel != CHIPC_CST_OTP_PWRDN)
			min_mask |= PMURES_BIT(RES4329_OTP_PU);

		/* Allow (but don't require) PLL to turn on */
		max_mask = 0x3ff63e;
		break;

	case BHND_CHIPID_BCM4319:
		/* We only need a few resources to be kept on all the time */
		min_mask = PMURES_BIT(RES4319_CBUCK_LPOM) |
		    PMURES_BIT(RES4319_CLDO_PU);

		/* Allow everything else to be turned on upon requests */
		max_mask = ~(~0 << rsrcs);
		break;

	case BHND_CHIPID_BCM4336:
		/* Down to save the power. */
		min_mask =
		    PMURES_BIT(RES4336_CBUCK_LPOM) |
		    PMURES_BIT(RES4336_CLDO_PU) |
		    PMURES_BIT(RES4336_LDO3P3_PU) |
		    PMURES_BIT(RES4336_OTP_PU) |
		    PMURES_BIT(RES4336_DIS_INT_RESET_PD);
		/* Allow (but don't require) PLL to turn on */
		max_mask = 0x1ffffff;
		break;

	case BHND_CHIPID_BCM4330:
		/* Down to save the power. */
		min_mask =
		    PMURES_BIT(RES4330_CBUCK_LPOM) | PMURES_BIT(RES4330_CLDO_PU)
		    | PMURES_BIT(RES4330_DIS_INT_RESET_PD) |
		    PMURES_BIT(RES4330_LDO3P3_PU) | PMURES_BIT(RES4330_OTP_PU);
		/* Allow (but don't require) PLL to turn on */
		max_mask = 0xfffffff;
		break;

	case BHND_CHIPID_BCM4313:
		min_mask = PMURES_BIT(RES4313_BB_PU_RSRC) |
		    PMURES_BIT(RES4313_XTAL_PU_RSRC) |
		    PMURES_BIT(RES4313_ALP_AVAIL_RSRC) |
		    PMURES_BIT(RES4313_BB_PLL_PWRSW_RSRC);
		max_mask = 0xffff;
		break;
	default:
		break;
	}

	/* Apply nvram override to min mask */
	error = bhnd_nvram_getvar_uint32(sc->chipc_dev, BHND_NVAR_RMIN, &nval);
	if (error && error != ENOENT) {
		PMU_LOG(sc, "NVRAM error reading %s: %d\n",
		    BHND_NVAR_RMIN, error);
		return (error);
	} else if (!error) {
		PMU_DEBUG(sc, "Applying rmin=%#x to min_mask\n", nval);
		min_mask = nval;
	}

	/* Apply nvram override to max mask */
	error = bhnd_nvram_getvar_uint32(sc->chipc_dev, BHND_NVAR_RMAX, &nval);
	if (error && error != ENOENT) {
		PMU_LOG(sc, "NVRAM error reading %s: %d\n",
		    BHND_NVAR_RMAX, error);
		return (error);
	} else if (!error) {
		PMU_DEBUG(sc, "Applying rmax=%#x to max_mask\n", nval);
		min_mask = nval;
	}

	if (pmin != NULL)
		*pmin = min_mask;

	if (pmax != NULL)
		*pmax = max_mask;

	return (0);
}