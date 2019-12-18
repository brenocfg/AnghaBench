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
br_mispredict_broad(struct counters *cpu, int pos)
{
	struct counters *brctr;
	struct counters *unhalt;
	struct counters *clear;
	struct counters *uops;
	struct counters *uops_ret;
	struct counters *recv;
	int ret;
	double br, cl, uo, uo_r, re, con, un, res;

	con = 4.0;
	
	unhalt = find_counter(cpu, "CPU_CLK_UNHALTED.THREAD_P");
        brctr = find_counter(cpu, "BR_MISP_RETIRED.ALL_BRANCHES");
	clear = find_counter(cpu, "MACHINE_CLEARS.CYCLES");
	uops = find_counter(cpu, "UOPS_ISSUED.ANY");
	uops_ret = find_counter(cpu, "UOPS_RETIRED.RETIRE_SLOTS");
	recv = find_counter(cpu, "INT_MISC.RECOVERY_CYCLES");

	if (pos != -1) {
		un = unhalt->vals[pos] * 1.0;
		br = brctr->vals[pos] * 1.0;
		cl = clear->vals[pos] * 1.0;
		uo = uops->vals[pos] * 1.0;
		uo_r = uops_ret->vals[pos] * 1.0;
		re = recv->vals[pos] * 1.0;
	} else {
		un = unhalt->sum * 1.0;
		br = brctr->sum * 1.0;
		cl = clear->sum * 1.0;
		uo = uops->sum * 1.0;
		uo_r = uops_ret->sum * 1.0;
		re = recv->sum * 1.0;
	}
	res = br / (br + cl) * (uo - uo_r + con * re) / (un * con);
 	ret = printf("%1.3f", res);
	return(ret);
}