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
allocstall2(struct counters *cpu, int pos)
{
/*  2  - PARTIAL_RAT_STALLS.FLAGS_MERGE_UOP_CYCLES/CPU_CLK_UNHALTED.THREAD_P (thresh >.05) */
	int ret;
	struct counters *partial;
	struct counters *unhalt;
	double un, par, res;
	unhalt = find_counter(cpu, "CPU_CLK_UNHALTED.THREAD_P");
	partial = find_counter(cpu, "PARTIAL_RAT_STALLS.FLAGS_MERGE_UOP");
	if (pos != -1) {
		par = partial->vals[pos] * 1.0;
		un = unhalt->vals[pos] * 1.0;
	} else {
		par = partial->sum * 1.0;
		un = unhalt->sum * 1.0;
	}
	res = par/un;
	ret = printf("%1.3f", res);
	return(ret);
}