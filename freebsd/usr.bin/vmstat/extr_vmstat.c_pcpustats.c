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
typedef  unsigned long u_long ;

/* Variables and functions */
 int CPUSTATES ; 
 int CP_IDLE ; 
 int CP_INTR ; 
 int CP_NICE ; 
 int CP_SYS ; 
 int CP_USER ; 
 double* cur_cp_times ; 
 double* last_cp_times ; 
 int /*<<< orphan*/  percent (char*,double,int*) ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,int) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

__attribute__((used)) static void
pcpustats(u_long cpumask, int maxid)
{
	double lpct, total;
	long tmp;
	int i, over, state;

	/* devstats does this for cp_time */
	for (i = 0; i <= maxid; i++) {
		if ((cpumask & (1ul << i)) == 0)
			continue;
		for (state = 0; state < CPUSTATES; ++state) {
			tmp = cur_cp_times[i * CPUSTATES + state];
			cur_cp_times[i * CPUSTATES + state] -= last_cp_times[i *
			    CPUSTATES + state];
			last_cp_times[i * CPUSTATES + state] = tmp;
		}
	}

	over = 0;
	xo_open_list("cpu");
	for (i = 0; i <= maxid; i++) {
		if ((cpumask & (1ul << i)) == 0)
			continue;
		xo_open_instance("cpu");
		xo_emit("{ke:name/%d}", i);
		total = 0;
		for (state = 0; state < CPUSTATES; ++state)
			total += cur_cp_times[i * CPUSTATES + state];
		if (total)
			lpct = 100.0 / total;
		else
			lpct = 0.0;
		percent("user", (cur_cp_times[i * CPUSTATES + CP_USER] +
		    cur_cp_times[i * CPUSTATES + CP_NICE]) * lpct, &over);
		percent("system", (cur_cp_times[i * CPUSTATES + CP_SYS] +
		    cur_cp_times[i * CPUSTATES + CP_INTR]) * lpct, &over);
		percent("idle", cur_cp_times[i * CPUSTATES + CP_IDLE] * lpct,
		    &over);
		xo_close_instance("cpu");
	}
	xo_close_list("cpu");
}