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
typedef  int uint32_t ;
struct bhnd_pmu_query {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PMU0_PLL0_PC0_DIV_ARM ; 
 int BHND_PMU0_PLL0_PC0_DIV_ARM_BASE ; 
 int BHND_PMU0_PLL0_PC0_PDIV_MASK ; 
 int /*<<< orphan*/  BHND_PMU0_PLL0_PC1_WILD_FRAC ; 
 int /*<<< orphan*/  BHND_PMU0_PLL0_PC2_WILD_INT ; 
 int /*<<< orphan*/  BHND_PMU0_PLL0_PLLCTL0 ; 
 int /*<<< orphan*/  BHND_PMU0_PLL0_PLLCTL1 ; 
 int /*<<< orphan*/  BHND_PMU0_PLL0_PLLCTL2 ; 
 int BHND_PMU_GET_BITS (int,int /*<<< orphan*/ ) ; 
 int BHND_PMU_PLL_READ (struct bhnd_pmu_query*,int /*<<< orphan*/ ) ; 
 int FVCO_880 ; 
 int /*<<< orphan*/  PMU0_PLL0_PC1_WILD_INT ; 
 int /*<<< orphan*/  PMU_DEBUG (struct bhnd_pmu_query*,char*,int,int,int) ; 
 int bhnd_pmu0_alpclk0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc ; 
 int /*<<< orphan*/  osh ; 
 int /*<<< orphan*/  sih ; 

__attribute__((used)) static uint32_t
bhnd_pmu0_cpuclk0(struct bhnd_pmu_query *sc)
{
	uint32_t tmp, divarm;
	uint32_t FVCO;
#ifdef BCMDBG
	uint32_t pdiv, wbint, wbfrac, fvco;
	uint32_t freq;
#endif

	FVCO = FVCO_880;

	/* Read divarm from pllcontrol[0] */
	tmp = BHND_PMU_PLL_READ(sc, BHND_PMU0_PLL0_PLLCTL0);
	divarm = BHND_PMU_GET_BITS(tmp, BHND_PMU0_PLL0_PC0_DIV_ARM);

#ifdef BCMDBG
	/* Calculate fvco based on xtal freq, pdiv, and wild */
	pdiv = tmp & BHND_PMU0_PLL0_PC0_PDIV_MASK;

	tmp = BHND_PMU_PLL_READ(sc, BHND_PMU0_PLL0_PLLCTL1);
	wbfrac = BHND_PMU_GET_BITS(tmp, BHND_PMU0_PLL0_PC1_WILD_FRAC);
	wbint = BHND_PMU_GET_BITS(tmp, PMU0_PLL0_PC1_WILD_INT);

	tmp = BHND_PMU_PLL_READ(sc, BHND_PMU0_PLL0_PLLCTL2);
	wbint += BHND_PMU_GET_BITS(tmp, BHND_PMU0_PLL0_PC2_WILD_INT);

	freq = bhnd_pmu0_alpclk0(sih, osh, cc) / 1000;

	fvco = (freq * wbint) << 8;
	fvco += (freq * (wbfrac >> 10)) >> 2;
	fvco += (freq * (wbfrac & 0x3ff)) >> 10;
	fvco >>= 8;
	fvco >>= pdiv;
	fvco /= 1000;
	fvco *= 1000;

	PMU_DEBUG(sc, "bhnd_pmu0_cpuclk0: wbint %u wbfrac %u fvco %u\n",
	         wbint, wbfrac, fvco);

	FVCO = fvco;
#endif	/* BCMDBG */

	/* Return ARM/SB clock */
	return FVCO / (divarm + BHND_PMU0_PLL0_PC0_DIV_ARM_BASE) * 1000;
}