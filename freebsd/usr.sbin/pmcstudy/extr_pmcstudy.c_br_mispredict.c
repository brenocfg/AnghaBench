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
br_mispredict(struct counters *cpu, int pos)
{
	struct counters *brctr;
	struct counters *unhalt;
	int ret;
/*  3  - (20 * BR_MISP_RETIRED.ALL_BRANCHES)/CPU_CLK_UNHALTED.THREAD_P (thresh >= .2) */
	double br, un, con, res;
	con = 20.0;
	
	unhalt = find_counter(cpu, "CPU_CLK_UNHALTED.THREAD_P");
        brctr = find_counter(cpu, "BR_MISP_RETIRED.ALL_BRANCHES");
	if (pos != -1) {
		br = brctr->vals[pos] * 1.0;
		un = unhalt->vals[pos] * 1.0;
	} else {
		br = brctr->sum * 1.0;
		un = unhalt->sum * 1.0;
	}
	res = (con * br)/un;
 	ret = printf("%1.3f", res);
	return(ret);
}