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
 int /*<<< orphan*/  BHND_PMU_CTRL ; 
 int BHND_PMU_CTRL_ALP_REQ_EN ; 
 int BHND_PMU_CTRL_HT_REQ_EN ; 
 int BHND_PMU_READ_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_WRITE_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int) ; 

uint32_t
bhnd_pmu_force_ilp(struct bhnd_pmu_softc *sc, bool force)
{
	uint32_t	orig;
	uint32_t	pctrl;

	pctrl = BHND_PMU_READ_4(sc, BHND_PMU_CTRL);
	orig = pctrl;

	if (force)
		pctrl &= ~(BHND_PMU_CTRL_HT_REQ_EN | BHND_PMU_CTRL_ALP_REQ_EN);
	else
		pctrl |= (BHND_PMU_CTRL_HT_REQ_EN | BHND_PMU_CTRL_ALP_REQ_EN);

	BHND_PMU_WRITE_4(sc, BHND_PMU_CTRL, pctrl);

	return (orig);
}