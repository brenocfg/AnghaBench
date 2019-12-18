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
struct TYPE_3__ {int chip_id; } ;
struct bhnd_pmu_query {TYPE_1__ cid; } ;
struct TYPE_4__ {int /*<<< orphan*/  pmurev; int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
#define  BHND_CHIPID_BCM43111 169 
#define  BHND_CHIPID_BCM43112 168 
#define  BHND_CHIPID_BCM4312 167 
#define  BHND_CHIPID_BCM4313 166 
#define  BHND_CHIPID_BCM43131 165 
#define  BHND_CHIPID_BCM4315 164 
#define  BHND_CHIPID_BCM4319 163 
#define  BHND_CHIPID_BCM4322 162 
#define  BHND_CHIPID_BCM43221 161 
#define  BHND_CHIPID_BCM43222 160 
#define  BHND_CHIPID_BCM43224 159 
#define  BHND_CHIPID_BCM43225 158 
#define  BHND_CHIPID_BCM43226 157 
#define  BHND_CHIPID_BCM43227 156 
#define  BHND_CHIPID_BCM43228 155 
#define  BHND_CHIPID_BCM43231 154 
#define  BHND_CHIPID_BCM43234 153 
#define  BHND_CHIPID_BCM43235 152 
#define  BHND_CHIPID_BCM43236 151 
#define  BHND_CHIPID_BCM43237 150 
#define  BHND_CHIPID_BCM43238 149 
#define  BHND_CHIPID_BCM4325 148 
#define  BHND_CHIPID_BCM4328 147 
#define  BHND_CHIPID_BCM4329 146 
#define  BHND_CHIPID_BCM4330 145 
#define  BHND_CHIPID_BCM4331 144 
#define  BHND_CHIPID_BCM4336 143 
#define  BHND_CHIPID_BCM4342 142 
#define  BHND_CHIPID_BCM43420 141 
#define  BHND_CHIPID_BCM43421 140 
#define  BHND_CHIPID_BCM43428 139 
#define  BHND_CHIPID_BCM43431 138 
#define  BHND_CHIPID_BCM4706 137 
#define  BHND_CHIPID_BCM4716 136 
#define  BHND_CHIPID_BCM47162 135 
#define  BHND_CHIPID_BCM4748 134 
#define  BHND_CHIPID_BCM4749 133 
#define  BHND_CHIPID_BCM5354 132 
#define  BHND_CHIPID_BCM5356 131 
#define  BHND_CHIPID_BCM5357 130 
#define  BHND_CHIPID_BCM53572 129 
#define  BHND_CHIPID_BCM6362 128 
 int BHND_PMU_ALP_CLOCK ; 
 int /*<<< orphan*/  PMU_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm_chipname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bhnd_pmu0_alpclk0 (struct bhnd_pmu_query*) ; 
 int bhnd_pmu1_alpclk0 (struct bhnd_pmu_query*) ; 
 int /*<<< orphan*/  chn ; 
 TYPE_2__* sih ; 

uint32_t
bhnd_pmu_alp_clock(struct bhnd_pmu_query *sc)
{
	uint32_t clock;

	clock = BHND_PMU_ALP_CLOCK;
	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4328:
	case BHND_CHIPID_BCM5354:
		clock = bhnd_pmu0_alpclk0(sc);
		break;
	case BHND_CHIPID_BCM4315:
	case BHND_CHIPID_BCM4319:
	case BHND_CHIPID_BCM4325:
	case BHND_CHIPID_BCM4329:
	case BHND_CHIPID_BCM4330:
	case BHND_CHIPID_BCM4336:
		clock = bhnd_pmu1_alpclk0(sc);
		break;
	case BHND_CHIPID_BCM4312:
	case BHND_CHIPID_BCM4322:
	case BHND_CHIPID_BCM43221:
	case BHND_CHIPID_BCM43231:
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
	case BHND_CHIPID_BCM4342:
	case BHND_CHIPID_BCM4716:
	case BHND_CHIPID_BCM4748:
	case BHND_CHIPID_BCM47162:
	case BHND_CHIPID_BCM4313:
	case BHND_CHIPID_BCM5357:
	case BHND_CHIPID_BCM4749:
	case BHND_CHIPID_BCM53572:
		/* always 20Mhz */
		clock = 20000 * 1000;
		break;
	case BHND_CHIPID_BCM5356:
	case BHND_CHIPID_BCM4706:
		/* always 25Mhz */
		clock = 25000 * 1000;
		break;
	default:
		PMU_DEBUG("No ALP clock specified "
			 "for chip %s rev %d pmurev %d, using default %d Hz\n",
			 bcm_chipname(sih->chip, chn, 8), sih->chiprev,
			 sih->pmurev, clock);
		break;
	}

	return (clock);
}