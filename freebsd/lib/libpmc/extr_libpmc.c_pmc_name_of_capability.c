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
typedef  enum pmc_caps { ____Placeholder_pmc_caps } pmc_caps ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int PMC_CAP_FIRST ; 
 int PMC_CAP_LAST ; 
 int /*<<< orphan*/  errno ; 
 int ffs (int) ; 
 char const** pmc_capability_names ; 

const char *
pmc_name_of_capability(enum pmc_caps cap)
{
	int i;

	/*
	 * 'cap' should have a single bit set and should be in
	 * range.
	 */
	if ((cap & (cap - 1)) || cap < PMC_CAP_FIRST ||
	    cap > PMC_CAP_LAST) {
		errno = EINVAL;
		return (NULL);
	}

	i = ffs(cap);
	return (pmc_capability_names[i - 1]);
}