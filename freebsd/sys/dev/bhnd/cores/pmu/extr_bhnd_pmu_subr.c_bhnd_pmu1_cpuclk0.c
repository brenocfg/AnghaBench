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
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC0_P1DIV ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC0_P2DIV ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC1_M1DIV ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC2_NDIV_INT ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC3_NDIV_FRAC ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PLLCTL0 ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PLLCTL1 ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PLLCTL2 ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PLLCTL3 ; 
 int BHND_PMU_GET_BITS (int,int /*<<< orphan*/ ) ; 
 int BHND_PMU_PLL_READ (struct bhnd_pmu_query*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMU_DEBUG (struct bhnd_pmu_query*,char*,int,int,int,int,int) ; 
 int bhnd_pmu1_alpclk0 (struct bhnd_pmu_query*) ; 
 int bhnd_pmu1_pllfvco0 (struct bhnd_pmu_query*) ; 

__attribute__((used)) static uint32_t
bhnd_pmu1_cpuclk0(struct bhnd_pmu_query *sc)
{
	uint32_t tmp, m1div;
#ifdef BCMDBG
	uint32_t ndiv_int, ndiv_frac, p2div, p1div, fvco;
	uint32_t fref;
#endif
	uint32_t FVCO = bhnd_pmu1_pllfvco0(sc);

	/* Read m1div from pllcontrol[1] */
	tmp = BHND_PMU_PLL_READ(sc, BHND_PMU1_PLL0_PLLCTL1);
	m1div = BHND_PMU_GET_BITS(tmp, BHND_PMU1_PLL0_PC1_M1DIV);

#ifdef BCMDBG
	/* Read p2div/p1div from pllcontrol[0] */
	tmp = BHND_PMU_PLL_READ(sc, BHND_PMU1_PLL0_PLLCTL0);
	p2div = BHND_PMU_GET_BITS(tmp, BHND_PMU1_PLL0_PC0_P2DIV);
	p1div = BHND_PMU_GET_BITS(tmp, BHND_PMU1_PLL0_PC0_P1DIV);

	/* Calculate fvco based on xtal freq and ndiv and pdiv */
	tmp = BHND_PMU_PLL_READ(sc, BHND_PMU1_PLL0_PLLCTL2);
	ndiv_int = BHND_PMU_GET_BITS(tmp, BHND_PMU1_PLL0_PC2_NDIV_INT);

	tmp = BHND_PMU_PLL_READ(sc, BHND_PMU1_PLL0_PLLCTL3);
	ndiv_frac = BHND_PMU_GET_BITS(tmp, BHND_PMU1_PLL0_PC3_NDIV_FRAC);

	fref = bhnd_pmu1_alpclk0(sc) / 1000;

	fvco = (fref * ndiv_int) << 8;
	fvco += (fref * (ndiv_frac >> 12)) >> 4;
	fvco += (fref * (ndiv_frac & 0xfff)) >> 12;
	fvco >>= 8;
	fvco *= p2div;
	fvco /= p1div;
	fvco /= 1000;
	fvco *= 1000;

	PMU_DEBUG(sc, "bhnd_pmu1_cpuclk0: ndiv_int %u ndiv_frac %u p2div %u "
	    "p1div %u fvco %u\n", ndiv_int, ndiv_frac, p2div, p1div, fvco);

	FVCO = fvco;
#endif				/* BCMDBG */

	/* Return ARM/SB clock */
	return (FVCO / m1div * 1000);
}