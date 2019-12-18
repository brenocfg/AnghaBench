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
typedef  enum pmc_disp { ____Placeholder_pmc_disp } pmc_disp ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int PMC_DISP_FIRST ; 
 int PMC_DISP_LAST ; 
 int /*<<< orphan*/  errno ; 
 char const** pmc_disposition_names ; 

const char *
pmc_name_of_disposition(enum pmc_disp pd)
{
	if ((int) pd >= PMC_DISP_FIRST &&
	    pd <= PMC_DISP_LAST)
		return (pmc_disposition_names[pd]);

	errno = EINVAL;
	return (NULL);
}