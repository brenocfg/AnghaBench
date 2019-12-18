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
typedef  enum pmc_cputype { ____Placeholder_pmc_cputype } pmc_cputype ;
struct TYPE_3__ {int pm_cputype; char const* pm_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 size_t PMC_TABLE_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* pmc_cputype_names ; 

const char *
pmc_name_of_cputype(enum pmc_cputype cp)
{
	size_t n;

	for (n = 0; n < PMC_TABLE_SIZE(pmc_cputype_names); n++)
		if (cp == pmc_cputype_names[n].pm_cputype)
			return (pmc_cputype_names[n].pm_name);

	errno = EINVAL;
	return (NULL);
}