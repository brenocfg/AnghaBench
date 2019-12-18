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
typedef  enum pmc_mode { ____Placeholder_pmc_mode } pmc_mode ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int PMC_MODE_FIRST ; 
 int PMC_MODE_LAST ; 
 int /*<<< orphan*/  errno ; 
 char const** pmc_mode_names ; 

const char *
pmc_name_of_mode(enum pmc_mode pm)
{
	if ((int) pm >= PMC_MODE_FIRST &&
	    pm <= PMC_MODE_LAST)
		return (pmc_mode_names[pm]);

	errno = EINVAL;
	return (NULL);
}