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
typedef  enum pmc_event { ____Placeholder_pmc_event } pmc_event ;
struct TYPE_2__ {int /*<<< orphan*/  pm_cputype; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 char* _pmc_name_of_event (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ cpu_info ; 
 int /*<<< orphan*/  errno ; 

const char *
pmc_name_of_event(enum pmc_event pe)
{
	const char *n;

	if ((n = _pmc_name_of_event(pe, cpu_info.pm_cputype)) != NULL)
		return (n);

	errno = EINVAL;
	return (NULL);
}