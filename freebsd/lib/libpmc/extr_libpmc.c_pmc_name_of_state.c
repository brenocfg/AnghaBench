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
typedef  enum pmc_state { ____Placeholder_pmc_state } pmc_state ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int PMC_STATE_FIRST ; 
 int PMC_STATE_LAST ; 
 int /*<<< orphan*/  errno ; 
 char const** pmc_state_names ; 

const char *
pmc_name_of_state(enum pmc_state ps)
{
	if ((int) ps >= PMC_STATE_FIRST &&
	    ps <= PMC_STATE_LAST)
		return (pmc_state_names[ps]);

	errno = EINVAL;
	return (NULL);
}