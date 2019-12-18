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
typedef  int uint32_t ;
struct TYPE_4__ {int chip_id; int /*<<< orphan*/  chip_rev; } ;
struct bhnd_pmu_query {TYPE_2__ cid; int /*<<< orphan*/  io_ctx; TYPE_1__* io; } ;
struct TYPE_3__ {int (* rd_chipst ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  BHND_CHIPID_BCM43111 164 
#define  BHND_CHIPID_BCM43112 163 
#define  BHND_CHIPID_BCM4312 162 
#define  BHND_CHIPID_BCM4313 161 
#define  BHND_CHIPID_BCM4315 160 
#define  BHND_CHIPID_BCM4319 159 
#define  BHND_CHIPID_BCM4322 158 
#define  BHND_CHIPID_BCM43221 157 
#define  BHND_CHIPID_BCM43222 156 
#define  BHND_CHIPID_BCM43224 155 
#define  BHND_CHIPID_BCM43225 154 
#define  BHND_CHIPID_BCM43226 153 
#define  BHND_CHIPID_BCM43231 152 
#define  BHND_CHIPID_BCM43234 151 
#define  BHND_CHIPID_BCM43235 150 
#define  BHND_CHIPID_BCM43236 149 
#define  BHND_CHIPID_BCM43237 148 
#define  BHND_CHIPID_BCM43238 147 
#define  BHND_CHIPID_BCM4325 146 
#define  BHND_CHIPID_BCM4328 145 
#define  BHND_CHIPID_BCM4329 144 
#define  BHND_CHIPID_BCM4330 143 
#define  BHND_CHIPID_BCM4331 142 
#define  BHND_CHIPID_BCM4336 141 
#define  BHND_CHIPID_BCM4342 140 
#define  BHND_CHIPID_BCM43420 139 
#define  BHND_CHIPID_BCM43421 138 
#define  BHND_CHIPID_BCM43431 137 
#define  BHND_CHIPID_BCM4706 136 
#define  BHND_CHIPID_BCM4716 135 
#define  BHND_CHIPID_BCM47162 134 
#define  BHND_CHIPID_BCM4748 133 
#define  BHND_CHIPID_BCM4749 132 
#define  BHND_CHIPID_BCM5356 131 
#define  BHND_CHIPID_BCM5357 130 
#define  BHND_CHIPID_BCM53572 129 
#define  BHND_CHIPID_BCM6362 128 
 int /*<<< orphan*/  BHND_PMU4706_MAINPLL_PLL0 ; 
 int /*<<< orphan*/  BHND_PMU4716_MAINPLL_PLL0 ; 
 int /*<<< orphan*/  BHND_PMU5356_MAINPLL_PLL0 ; 
 int /*<<< orphan*/  BHND_PMU5357_MAINPLL_PLL0 ; 
 int /*<<< orphan*/  BHND_PMU5_MAINPLL_SI ; 
 int /*<<< orphan*/  BHND_PMU6_MAINPLL_SI ; 
 int BHND_PMU_HT_CLOCK ; 
 int /*<<< orphan*/  BHND_PMU_REV (struct bhnd_pmu_query*) ; 
 int CHIPC_CST43236_BP_CLK ; 
 int CHIPC_CST43237_BP_CLK ; 
 int /*<<< orphan*/  PMU_LOG (struct bhnd_pmu_query*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bhnd_pmu0_cpuclk0 (struct bhnd_pmu_query*) ; 
 int bhnd_pmu1_cpuclk0 (struct bhnd_pmu_query*) ; 
 int bhnd_pmu5_clock (struct bhnd_pmu_query*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bhnd_pmu6_4706_clock (struct bhnd_pmu_query*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 

uint32_t
bhnd_pmu_si_clock(struct bhnd_pmu_query *sc)
{
	uint32_t chipst;
	uint32_t clock;

	clock = BHND_PMU_HT_CLOCK;

	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4322:
	case BHND_CHIPID_BCM43221:
	case BHND_CHIPID_BCM43231:
	case BHND_CHIPID_BCM43222:
	case BHND_CHIPID_BCM43111:
	case BHND_CHIPID_BCM43112:
	case BHND_CHIPID_BCM43224:
	case BHND_CHIPID_BCM43420:
	case BHND_CHIPID_BCM43225:
	case BHND_CHIPID_BCM43421:
	case BHND_CHIPID_BCM43226:
	case BHND_CHIPID_BCM4331:
	case BHND_CHIPID_BCM43431:
	case BHND_CHIPID_BCM6362:
	case BHND_CHIPID_BCM4342:
		/* 96MHz backplane clock */
		clock = 96000 * 1000;
		break;

	case BHND_CHIPID_BCM4716:
	case BHND_CHIPID_BCM4748:
	case BHND_CHIPID_BCM47162:
		clock = bhnd_pmu5_clock(sc, BHND_PMU4716_MAINPLL_PLL0,
		    BHND_PMU5_MAINPLL_SI);
		break;

	case BHND_CHIPID_BCM4325:
		clock = bhnd_pmu1_cpuclk0(sc);
		break;

	case BHND_CHIPID_BCM4328:
		clock = bhnd_pmu0_cpuclk0(sc);
		break;

	case BHND_CHIPID_BCM4329:
		if (sc->cid.chip_rev == 0)
			clock = 38400 * 1000;
		else
			clock = bhnd_pmu1_cpuclk0(sc);
		break;

	case BHND_CHIPID_BCM4315:
	case BHND_CHIPID_BCM4319:
	case BHND_CHIPID_BCM4336:
	case BHND_CHIPID_BCM4330:
		clock = bhnd_pmu1_cpuclk0(sc);
		break;

	case BHND_CHIPID_BCM4312:
	case BHND_CHIPID_BCM4313:
		/* 80MHz backplane clock */
		clock = 80000 * 1000;
		break;

	case BHND_CHIPID_BCM43234:
	case BHND_CHIPID_BCM43235:
	case BHND_CHIPID_BCM43236:
	case BHND_CHIPID_BCM43238:
		chipst = sc->io->rd_chipst(sc->io_ctx);
		if (chipst & CHIPC_CST43236_BP_CLK)
			clock = 120000 * 1000;
		else
			clock = 96000 * 1000;
		break;
	case BHND_CHIPID_BCM43237:
		chipst = sc->io->rd_chipst(sc->io_ctx);
		if (chipst & CHIPC_CST43237_BP_CLK)
			clock = 96000 * 1000;
		else
			clock = 80000 * 1000;
		break;
	case BHND_CHIPID_BCM5356:
		clock = bhnd_pmu5_clock(sc, BHND_PMU5356_MAINPLL_PLL0,
		    BHND_PMU5_MAINPLL_SI);
		break;
	case BHND_CHIPID_BCM5357:
	case BHND_CHIPID_BCM4749:
		clock = bhnd_pmu5_clock(sc, BHND_PMU5357_MAINPLL_PLL0,
		    BHND_PMU5_MAINPLL_SI);
		break;
	case BHND_CHIPID_BCM4706:
		clock = bhnd_pmu6_4706_clock(sc, BHND_PMU4706_MAINPLL_PLL0,
		    BHND_PMU6_MAINPLL_SI);
		break;
	case BHND_CHIPID_BCM53572:
		clock = 75000000;
		break;
	default:
		PMU_LOG(sc, "No backplane clock specified for chip %#hx rev "
		    "%hhd pmurev %hhd, using default %dHz\n",
		    sc->cid.chip_id, sc->cid.chip_rev, BHND_PMU_REV(sc), clock);
		break;
	}

	return (clock);
}