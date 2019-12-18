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
struct TYPE_2__ {scalar_t__ chip_id; int chip_rev; } ;
struct bhnd_pmu_softc {int /*<<< orphan*/  chipc_dev; TYPE_1__ cid; } ;

/* Variables and functions */
 scalar_t__ BHND_CHIPID_BCM4319 ; 
 scalar_t__ BHND_CHIPID_BCM4329 ; 
 int /*<<< orphan*/  BHND_NVAR_XTALFREQ ; 
 int /*<<< orphan*/  BHND_PMU_AND_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_CTRL ; 
 int /*<<< orphan*/  BHND_PMU_CTRL_NOILP_ON_WAIT ; 
 int /*<<< orphan*/  BHND_PMU_OR_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_REGCTRL_WRITE (struct bhnd_pmu_softc*,int,int,int) ; 
 int BHND_PMU_REV (struct bhnd_pmu_softc*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  PMU_LOG (struct bhnd_pmu_softc*,char*,int) ; 
 int bhnd_nvram_getvar_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_pmu_measure_alpclk (struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  bhnd_pmu_pll_init (struct bhnd_pmu_softc*,int /*<<< orphan*/ ) ; 
 int bhnd_pmu_res_init (struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  bhnd_pmu_swreg_init (struct bhnd_pmu_softc*) ; 

int 
bhnd_pmu_init(struct bhnd_pmu_softc *sc)
{
	uint32_t	xtalfreq;
	int		error;

	if (BHND_PMU_REV(sc) == 1) {
		BHND_PMU_AND_4(sc, BHND_PMU_CTRL, ~BHND_PMU_CTRL_NOILP_ON_WAIT);
	} else if (BHND_PMU_REV(sc) >= 2) {
		BHND_PMU_OR_4(sc, BHND_PMU_CTRL, BHND_PMU_CTRL_NOILP_ON_WAIT);
	}

	if (sc->cid.chip_id == BHND_CHIPID_BCM4329 && sc->cid.chip_rev == 2) {
		/* Fix for 4329b0 bad LPOM state. */
		BHND_PMU_REGCTRL_WRITE(sc, 2, 0x100, ~0);
		BHND_PMU_REGCTRL_WRITE(sc, 3, 0x4, ~0);
	}

	if (sc->cid.chip_id == BHND_CHIPID_BCM4319) {
		/* Limiting the PALDO spike during init time */
		BHND_PMU_REGCTRL_WRITE(sc, 2, 0x00000005, 0x00000007);
	}


	/* Fetch target xtalfreq, in KHz */
	error = bhnd_nvram_getvar_uint32(sc->chipc_dev, BHND_NVAR_XTALFREQ,
	    &xtalfreq);

	/* If not available, log any real errors, and then try to measure it */
	if (error) {
		if (error != ENOENT)
			PMU_LOG(sc, "error fetching xtalfreq: %d\n", error);

		xtalfreq = bhnd_pmu_measure_alpclk(sc);
	}

	/* Perform PLL initialization */
	bhnd_pmu_pll_init(sc, xtalfreq);

	if ((error = bhnd_pmu_res_init(sc)))
		return (error);

	bhnd_pmu_swreg_init(sc);

	return (0);
}