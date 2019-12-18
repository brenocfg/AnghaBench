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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
struct TYPE_2__ {int chip_id; int /*<<< orphan*/  chip_rev; } ;
struct bhnd_pmu_softc {TYPE_1__ cid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_CCS_HTAVAIL ; 
#define  BHND_CHIPID_BCM43111 161 
#define  BHND_CHIPID_BCM43112 160 
#define  BHND_CHIPID_BCM4312 159 
#define  BHND_CHIPID_BCM4313 158 
#define  BHND_CHIPID_BCM43131 157 
#define  BHND_CHIPID_BCM4315 156 
#define  BHND_CHIPID_BCM4319 155 
#define  BHND_CHIPID_BCM4322 154 
#define  BHND_CHIPID_BCM43221 153 
#define  BHND_CHIPID_BCM43222 152 
#define  BHND_CHIPID_BCM43224 151 
#define  BHND_CHIPID_BCM43225 150 
#define  BHND_CHIPID_BCM43226 149 
#define  BHND_CHIPID_BCM43227 148 
#define  BHND_CHIPID_BCM43228 147 
#define  BHND_CHIPID_BCM43231 146 
#define  BHND_CHIPID_BCM43234 145 
#define  BHND_CHIPID_BCM43235 144 
#define  BHND_CHIPID_BCM43236 143 
#define  BHND_CHIPID_BCM43237 142 
#define  BHND_CHIPID_BCM43238 141 
#define  BHND_CHIPID_BCM4325 140 
#define  BHND_CHIPID_BCM4328 139 
#define  BHND_CHIPID_BCM4329 138 
#define  BHND_CHIPID_BCM4330 137 
#define  BHND_CHIPID_BCM4331 136 
#define  BHND_CHIPID_BCM4336 135 
#define  BHND_CHIPID_BCM4342 134 
#define  BHND_CHIPID_BCM43420 133 
#define  BHND_CHIPID_BCM43421 132 
#define  BHND_CHIPID_BCM43428 131 
#define  BHND_CHIPID_BCM43431 130 
#define  BHND_CHIPID_BCM5354 129 
#define  BHND_CHIPID_BCM6362 128 
 int /*<<< orphan*/  BHND_PMU2_SI_PLL_PLLCTL ; 
 int /*<<< orphan*/  BHND_PMU_AND_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_MAX_RES_MASK ; 
 int /*<<< orphan*/  BHND_PMU_MIN_RES_MASK ; 
 int /*<<< orphan*/  BHND_PMU_PLL_WRITE (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_READ_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_REV (struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  BHND_PMU_WRITE_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PMURES_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMU_DEBUG (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMU_WAIT_CLKST (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RES4322_HT_SI_AVAIL ; 
 int /*<<< orphan*/  RES4322_SI_PLL_ON ; 
 int /*<<< orphan*/  bhnd_pmu0_pllinit0 (struct bhnd_pmu_softc*,int) ; 
 int /*<<< orphan*/  bhnd_pmu1_pllinit0 (struct bhnd_pmu_softc*,int) ; 

void 
bhnd_pmu_pll_init(struct bhnd_pmu_softc *sc, u_int xtalfreq)
{
	uint32_t max_mask, min_mask;
	uint32_t res_ht, res_pll;

	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4312:
		/* assume default works */
		break;
	case BHND_CHIPID_BCM4322:
	case BHND_CHIPID_BCM43221:
	case BHND_CHIPID_BCM43231:
	case BHND_CHIPID_BCM4342:
		if (sc->cid.chip_rev != 0)
			break;

		min_mask = BHND_PMU_READ_4(sc, BHND_PMU_MIN_RES_MASK);
		max_mask = BHND_PMU_READ_4(sc, BHND_PMU_MIN_RES_MASK);
		res_ht = PMURES_BIT(RES4322_HT_SI_AVAIL);
		res_pll = PMURES_BIT(RES4322_SI_PLL_ON);

		/* Have to remove HT Avail request before powering off PLL */
		BHND_PMU_AND_4(sc, BHND_PMU_MIN_RES_MASK, ~res_ht);
		BHND_PMU_AND_4(sc, BHND_PMU_MAX_RES_MASK, ~res_ht);
		PMU_WAIT_CLKST(sc, 0, BHND_CCS_HTAVAIL);

		/* Make sure the PLL is off */
		BHND_PMU_AND_4(sc, BHND_PMU_MIN_RES_MASK, ~res_pll);
		BHND_PMU_AND_4(sc, BHND_PMU_MAX_RES_MASK, ~res_pll);
		PMU_WAIT_CLKST(sc, 0, BHND_CCS_HTAVAIL);

		DELAY(1000);

		BHND_PMU_PLL_WRITE(sc, BHND_PMU2_SI_PLL_PLLCTL, 0x380005c0, ~0);
		DELAY(100);

		BHND_PMU_WRITE_4(sc, BHND_PMU_MAX_RES_MASK, max_mask);
		DELAY(100);
		BHND_PMU_WRITE_4(sc, BHND_PMU_MIN_RES_MASK, min_mask);
		DELAY(100);

		break;
	case BHND_CHIPID_BCM4325:
		bhnd_pmu1_pllinit0(sc, xtalfreq);
		break;
	case BHND_CHIPID_BCM4328:
		bhnd_pmu0_pllinit0(sc, xtalfreq);
		break;
	case BHND_CHIPID_BCM5354:
		if (xtalfreq == 0)
			xtalfreq = 25000;
		bhnd_pmu0_pllinit0(sc, xtalfreq);
		break;
	case BHND_CHIPID_BCM4329:
		if (xtalfreq == 0)
			xtalfreq = 38400;
		bhnd_pmu1_pllinit0(sc, xtalfreq);
		break;

	case BHND_CHIPID_BCM4313:
	case BHND_CHIPID_BCM43222:
	case BHND_CHIPID_BCM43111:
	case BHND_CHIPID_BCM43112:
	case BHND_CHIPID_BCM43224:
	case BHND_CHIPID_BCM43225:
	case BHND_CHIPID_BCM43420:
	case BHND_CHIPID_BCM43421:
	case BHND_CHIPID_BCM43226:
	case BHND_CHIPID_BCM43235:
	case BHND_CHIPID_BCM43236:
	case BHND_CHIPID_BCM43238:
	case BHND_CHIPID_BCM43234:
	case BHND_CHIPID_BCM43237:
	case BHND_CHIPID_BCM4331:
	case BHND_CHIPID_BCM43431:
	case BHND_CHIPID_BCM43131:
	case BHND_CHIPID_BCM43227:
	case BHND_CHIPID_BCM43228:
	case BHND_CHIPID_BCM43428:
	case BHND_CHIPID_BCM6362:
		/* assume default works */
		break;

	case BHND_CHIPID_BCM4315:
	case BHND_CHIPID_BCM4319:
	case BHND_CHIPID_BCM4336:
	case BHND_CHIPID_BCM4330:
		bhnd_pmu1_pllinit0(sc, xtalfreq);
		break;
	default:
		PMU_DEBUG("No PLL init done for chip %#hx rev %d pmurev %d\n",
		    sc->cid.chip_id, sc->cid.chip_rev, BHND_PMU_REV(sc));
		break;
	}
}