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
struct counters {int cpu; struct counters* next_cpu; } ;

/* Variables and functions */
 int MAX_CPU ; 
 struct counters* cnts ; 
 struct counters** glob_cpu ; 
 int ncnts ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
lace_cpus_together(void)
{
	int i, j, lace_cpu;
	struct counters *cpat, *at;

	for(i=0; i<ncnts; i++) {
		cpat = &cnts[i];
		if (cpat->next_cpu) {
			/* Already laced in */
			continue;
		}
		lace_cpu = cpat->cpu;
		if (lace_cpu >= MAX_CPU) {
			printf("CPU %d to big\n", lace_cpu);
			continue;
		}
		if (glob_cpu[lace_cpu] == NULL) {
			glob_cpu[lace_cpu] = cpat;
		} else {
			/* Already processed this cpu */
			continue;
		}
		/* Ok look forward for cpu->cpu and link in */
		for(j=(i+1); j<ncnts; j++) {
			at = &cnts[j];
			if (at->next_cpu) {
				continue;
			}
			if (at->cpu == lace_cpu) {
				/* Found one */
				cpat->next_cpu = at;
				cpat = at;
			}
		}
	}
}