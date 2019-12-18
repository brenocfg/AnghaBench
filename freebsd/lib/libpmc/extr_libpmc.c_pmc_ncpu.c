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
struct TYPE_2__ {int pm_ncpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 TYPE_1__ cpu_info ; 
 int /*<<< orphan*/  errno ; 
 int pmc_syscall ; 

int
pmc_ncpu(void)
{
	if (pmc_syscall == -1) {
		errno = ENXIO;
		return (-1);
	}

	return (cpu_info.pm_ncpu);
}