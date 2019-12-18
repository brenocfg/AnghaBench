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
struct TYPE_2__ {int /*<<< orphan*/ ** times; } ;

/* Variables and functions */
 int STEP_BIND ; 
 int STEP_CNT ; 
 int connections ; 
 float diff_us (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* nodes ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  src_addr ; 
 char** step_str ; 
 int /*<<< orphan*/ ** times ; 
 int /*<<< orphan*/  zero_time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void show_perf(void)
{
	int c, i;
	float us, max[STEP_CNT], min[STEP_CNT];

	for (i = 0; i < STEP_CNT; i++) {
		max[i] = 0;
		min[i] = 999999999.;
		for (c = 0; c < connections; c++) {
			if (!zero_time(&nodes[c].times[i][0]) &&
			    !zero_time(&nodes[c].times[i][1])) {
				us = diff_us(&nodes[c].times[i][1], &nodes[c].times[i][0]);
				if (us > max[i])
					max[i] = us;
				if (us < min[i])
					min[i] = us;
			}
		}
	}

	printf("step              total ms     max ms     min us  us / conn\n");
	for (i = 0; i < STEP_CNT; i++) {
		if (i == STEP_BIND && !src_addr)
			continue;

		us = diff_us(&times[i][1], &times[i][0]);
		printf("%-13s: %11.2f%11.2f%11.2f%11.2f\n", step_str[i], us / 1000.,
			max[i] / 1000., min[i], us / connections);
	}
}