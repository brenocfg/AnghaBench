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
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  ipi_selected (int /*<<< orphan*/ ,int) ; 

void
ipi_all_but_self(int ipi)
{
	cpuset_t other_cpus;

	other_cpus = all_cpus;
	CPU_CLR(PCPU_GET(cpuid), &other_cpus);
	ipi_selected(other_cpus, ipi);
}