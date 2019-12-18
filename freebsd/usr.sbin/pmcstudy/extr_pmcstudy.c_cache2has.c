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
cache2has(struct counters *cpu, int pos)
{
	/*
	 * Examine ((MEM_LOAD_UOPS_RETIRED.LLC_HIT * 36) + \
	 *          (MEM_LOAD_UOPS_LLC_HIT_RETIRED.XSNP_HIT * 72) +
	 *          (MEM_LOAD_UOPS_LLC_HIT_RETIRED.XSNP_HITM * 84))
	 *           / CPU_CLK_UNHALTED.THREAD_P
	 */
	int ret;
	struct counters *mem1, *mem2, *mem3;
	struct counters *unhalt;
	double con1, con2, con3, un, me1, me2, me3, res;

	con1 = 36.0;
	con2 = 72.0;
	con3 = 84.0;
	unhalt = find_counter(cpu, "CPU_CLK_UNHALTED.THREAD_P");
	mem1 = find_counter(cpu, "MEM_LOAD_UOPS_RETIRED.LLC_HIT");
	mem2 = find_counter(cpu, "MEM_LOAD_UOPS_LLC_HIT_RETIRED.XSNP_HIT");
	mem3 = find_counter(cpu, "MEM_LOAD_UOPS_LLC_HIT_RETIRED.XSNP_HITM");
	if (pos != -1) {
		me1 = mem1->vals[pos] * 1.0;
		me2 = mem2->vals[pos] * 1.0;
		me3 = mem3->vals[pos] * 1.0;
		un = unhalt->vals[pos] * 1.0;
	} else {
		me1 = mem1->sum * 1.0;
		me2 = mem2->sum * 1.0;
		me3 = mem3->sum * 1.0;
		un = unhalt->sum * 1.0;
	}
	res = ((me1 * con1) + (me2 * con2) + (me3 * con3))/un;
	ret = printf("%1.3f", res);
	return(ret);
}