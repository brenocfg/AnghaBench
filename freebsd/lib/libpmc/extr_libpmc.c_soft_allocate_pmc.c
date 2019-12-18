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
struct pmc_op_pmcallocate {int pm_caps; } ;
typedef  enum pmc_event { ____Placeholder_pmc_event } pmc_event ;

/* Variables and functions */
 int PMC_CAP_READ ; 
 int PMC_CAP_WRITE ; 
 int PMC_EV_SOFT_FIRST ; 
 int PMC_EV_SOFT_LAST ; 

__attribute__((used)) static int
soft_allocate_pmc(enum pmc_event pe, char *ctrspec,
    struct pmc_op_pmcallocate *pmc_config)
{
	(void)ctrspec;
	(void)pmc_config;

	if ((int)pe < PMC_EV_SOFT_FIRST || (int)pe > PMC_EV_SOFT_LAST)
		return (-1);

	pmc_config->pm_caps |= (PMC_CAP_READ | PMC_CAP_WRITE);
	return (0);
}