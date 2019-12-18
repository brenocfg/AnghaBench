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
struct bhnd_pmu_softc {int dummy; } ;

/* Variables and functions */
 int BHND_PMU_GET_BITS (int,int /*<<< orphan*/ ) ; 
 int BHND_PMU_READ_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ) ; 
 int BHND_PMU_REV (struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  BHND_PMU_ST ; 
 int BHND_PMU_ST_EXTLPOAVAIL ; 
 int /*<<< orphan*/  BHND_PMU_WRITE_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  BHND_PMU_XTALFREQ ; 
 int /*<<< orphan*/  BHND_PMU_XTALFREQ_REG_ILPCTR ; 
 unsigned int BHND_PMU_XTALFREQ_REG_MEASURE_SHIFT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EXT_ILP_HZ ; 

uint32_t
bhnd_pmu_measure_alpclk(struct bhnd_pmu_softc *sc)
{
	uint32_t alp_khz;
	uint32_t pmu_st;

	if (BHND_PMU_REV(sc) < 10)
		return (0);

	pmu_st = BHND_PMU_READ_4(sc, BHND_PMU_ST);
	if (pmu_st & BHND_PMU_ST_EXTLPOAVAIL) {
		uint32_t alp_hz, ilp_ctr;

		/* Enable frequency measurement */
		BHND_PMU_WRITE_4(sc, BHND_PMU_XTALFREQ, 1U <<
		    BHND_PMU_XTALFREQ_REG_MEASURE_SHIFT);

		/* Delay for well over 4 ILP clocks */
		DELAY(1000);

		/* Read the latched number of ALP ticks per 4 ILP ticks */
		ilp_ctr = BHND_PMU_READ_4(sc, BHND_PMU_XTALFREQ);
		ilp_ctr = BHND_PMU_GET_BITS(ilp_ctr,
		    BHND_PMU_XTALFREQ_REG_ILPCTR);

		/* Turn off PMU_XTALFREQ_REG_MEASURE to save power */
		BHND_PMU_WRITE_4(sc, BHND_PMU_XTALFREQ, 0);

		/* Calculate ALP frequency */
		alp_hz = (ilp_ctr * EXT_ILP_HZ) / 4;

		/* Round to nearest 100KHz and convert to KHz */
		alp_khz = (alp_hz + 50000) / 100000 * 100;
	} else {
		alp_khz = 0;
	}

	return (alp_khz);
}