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
struct ti_cpufreq_data {TYPE_1__* soc_data; } ;
struct TYPE_2__ {unsigned long efuse_fallback; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long amx3_efuse_xlate(struct ti_cpufreq_data *opp_data,
				      unsigned long efuse)
{
	if (!efuse)
		efuse = opp_data->soc_data->efuse_fallback;
	/* AM335x and AM437x use "OPP disable" bits, so invert */
	return ~efuse;
}