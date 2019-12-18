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
struct bhnd_pmu_softc {int /*<<< orphan*/  query; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC1_M1DIV ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC1_M2DIV ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC1_M3DIV ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC1_M4DIV ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC2_M5DIV ; 
 int BHND_PMU1_PLL0_PC2_M5DIV_MASK ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PC2_M6DIV ; 
 int BHND_PMU1_PLL0_PC2_M6DIV_MASK ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PLLCTL1 ; 
 int /*<<< orphan*/  BHND_PMU1_PLL0_PLLCTL2 ; 
 int /*<<< orphan*/  BHND_PMU_PLL_WRITE (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int,int) ; 
 int BHND_PMU_SET_BITS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ PMU_CST4330_SDIOD_CHIPMODE (struct bhnd_pmu_softc*) ; 
 int bhnd_pmu1_pllfvco0 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
bhnd_pmu_set_4330_plldivs(struct bhnd_pmu_softc *sc)
{
	uint32_t FVCO = bhnd_pmu1_pllfvco0(&sc->query) / 1000;
	uint32_t m1div, m2div, m3div, m4div, m5div, m6div;
	uint32_t pllc1, pllc2;

	m2div = m3div = m4div = m6div = FVCO / 80;
	m5div = FVCO / 160;

	if (PMU_CST4330_SDIOD_CHIPMODE(sc))
		m1div = FVCO / 80;
	else
		m1div = FVCO / 90;

	pllc1 = 0;
	pllc1 |= BHND_PMU_SET_BITS(m1div, BHND_PMU1_PLL0_PC1_M1DIV);
	pllc1 |= BHND_PMU_SET_BITS(m2div, BHND_PMU1_PLL0_PC1_M2DIV);
	pllc1 |= BHND_PMU_SET_BITS(m3div, BHND_PMU1_PLL0_PC1_M3DIV);
	pllc1 |= BHND_PMU_SET_BITS(m4div, BHND_PMU1_PLL0_PC1_M4DIV);

	BHND_PMU_PLL_WRITE(sc, BHND_PMU1_PLL0_PLLCTL1, pllc1, ~0);

	pllc2 = 0;
	pllc2 |= BHND_PMU_SET_BITS(m5div, BHND_PMU1_PLL0_PC2_M5DIV);
	pllc2 |= BHND_PMU_SET_BITS(m6div, BHND_PMU1_PLL0_PC2_M6DIV);

	BHND_PMU_PLL_WRITE(sc, BHND_PMU1_PLL0_PLLCTL2, pllc2,
	    BHND_PMU1_PLL0_PC2_M5DIV_MASK | BHND_PMU1_PLL0_PC2_M6DIV_MASK);
}