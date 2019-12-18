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
 int /*<<< orphan*/  CPU_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 int strspn (char*,char*) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmcstat_get_cpumask(const char *cpuspec, cpuset_t *cpumask)
{
	int cpu;
	const char *s;
	char *end;

	CPU_ZERO(cpumask);
	s = cpuspec;

	do {
		cpu = strtol(s, &end, 0);
		if (cpu < 0 || end == s)
			errx(EX_USAGE,
			    "ERROR: Illegal CPU specification \"%s\".",
			    cpuspec);
		CPU_SET(cpu, cpumask);
		s = end + strspn(end, ", \t");
	} while (*s);
	assert(!CPU_EMPTY(cpumask));
}