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
 int /*<<< orphan*/  CPU_EMPTY (int /*<<< orphan*/  const*) ; 
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/  const*) ; 
 int CPU_SETSIZE ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_cpus(const char *banner, const cpuset_t *cpus)
{
	int i, first;

	first = 1;
	printf("%s:\t", banner);
	if (!CPU_EMPTY(cpus)) {
		for (i = 0; i < CPU_SETSIZE; i++) {
			if (CPU_ISSET(i, cpus)) {
				printf("%s%d", first ? " " : ", ", i);
				first = 0;
			}
		}
	} else
		printf(" (none)");
	printf("\n");
}