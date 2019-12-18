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
struct pmc_cpuinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 struct pmc_cpuinfo cpu_info ; 
 int /*<<< orphan*/  errno ; 
 int pmc_syscall ; 

int
pmc_cpuinfo(const struct pmc_cpuinfo **pci)
{
	if (pmc_syscall == -1) {
		errno = ENXIO;
		return (-1);
	}

	*pci = &cpu_info;
	return (0);
}