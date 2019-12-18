#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct bhnd_pmu_query {int dummy; } ;
struct TYPE_3__ {int freq; scalar_t__ xf; } ;
typedef  TYPE_1__ pmu0_xtaltab0_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PMU_CTRL ; 
 int /*<<< orphan*/  BHND_PMU_CTRL_XTALFREQ ; 
 scalar_t__ BHND_PMU_GET_BITS (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ BHND_PMU_READ_4 (struct bhnd_pmu_query*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 TYPE_1__* pmu0_xtaltab0 ; 

__attribute__((used)) static uint32_t
bhnd_pmu0_alpclk0(struct bhnd_pmu_query *sc)
{
	const pmu0_xtaltab0_t	*xt;
	uint32_t		 xf;

	/* Find the frequency in the table */
	xf = BHND_PMU_READ_4(sc, BHND_PMU_CTRL);
	xf = BHND_PMU_GET_BITS(xf, BHND_PMU_CTRL_XTALFREQ);
	for (xt = pmu0_xtaltab0; xt->freq; xt++)
		if (xt->xf == xf)
			break;

	/* PLL must be configured before */
	if (xt == NULL || xt->freq == 0)
		panic("unsupported frequency: %u", xf);

	return (xt->freq * 1000);
}