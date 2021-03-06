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
struct counters {double* vals; double sum; } ;

/* Variables and functions */
 struct counters* find_counter (struct counters*,char*) ; 
 int printf (char*,double) ; 

__attribute__((used)) static int
dtlb_missload(struct counters *cpu, int pos)
{
	/* 10  - ((DTLB_LOAD_MISSES.STLB_HIT * 7) + DTLB_LOAD_MISSES.WALK_DURATION) / CPU_CLK_UNHALTED.THREAD_P (t >=.1) */
	int ret;
	struct counters *dtlb_m, *dtlb_d;
	struct counters *unhalt;
	double con, un, d1, d2, res;

	con = 7.0;
	unhalt = find_counter(cpu, "CPU_CLK_UNHALTED.THREAD_P");
	dtlb_m = find_counter(cpu, "DTLB_LOAD_MISSES.STLB_HIT");
	dtlb_d = find_counter(cpu, "DTLB_LOAD_MISSES.WALK_DURATION");
	if (pos != -1) {
		d1 = dtlb_m->vals[pos] * 1.0;
		d2 = dtlb_d->vals[pos] * 1.0;
		un = unhalt->vals[pos] * 1.0;
	} else {
		d1 = dtlb_m->sum * 1.0;
		d2 = dtlb_d->sum * 1.0;
		un = unhalt->sum * 1.0;
	}
	res = ((d1 * con) + d2)/un;
	ret = printf("%1.3f", res);
	return(ret);
}