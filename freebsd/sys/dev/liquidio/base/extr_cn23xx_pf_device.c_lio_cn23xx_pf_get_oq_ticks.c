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
typedef  int uint32_t ;
struct TYPE_2__ {int coproc_tics_per_us; } ;
struct octeon_device {TYPE_1__ pfvf_hsword; } ;

/* Variables and functions */
 int lio_cn23xx_pf_coprocessor_clock (struct octeon_device*) ; 

uint32_t
lio_cn23xx_pf_get_oq_ticks(struct octeon_device *oct, uint32_t time_intr_in_us)
{
	/* This gives the SLI clock per microsec */
	uint32_t	oqticks_per_us = lio_cn23xx_pf_coprocessor_clock(oct);

	oct->pfvf_hsword.coproc_tics_per_us = oqticks_per_us;

	/* This gives the clock cycles per millisecond */
	oqticks_per_us *= 1000;

	/* This gives the oq ticks (1024 core clock cycles) per millisecond */
	oqticks_per_us /= 1024;

	/*
	 * time_intr is in microseconds. The next 2 steps gives the oq ticks
	 * corresponding to time_intr.
	 */
	oqticks_per_us *= time_intr_in_us;
	oqticks_per_us /= 1000;

	return (oqticks_per_us);
}