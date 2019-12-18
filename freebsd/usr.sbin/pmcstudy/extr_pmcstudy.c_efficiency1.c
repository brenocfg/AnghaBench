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
efficiency1(struct counters *cpu, int pos)
{

	int ret;	
	struct counters *uops;
	struct counters *unhalt;
	double un, ot, con, res;

        /* 19 (UOPS_RETIRED.RETIRE_SLOTS/(4*CPU_CLK_UNHALTED.THREAD_P) look if thresh < .9*/
	con = 4.0;
	unhalt = find_counter(cpu, "CPU_CLK_UNHALTED.THREAD_P");
	uops = find_counter(cpu, "UOPS_RETIRED.RETIRE_SLOTS");
	if (pos != -1) {
		ot = uops->vals[pos] * 1.0;
		un = unhalt->vals[pos] * 1.0;
	} else {
		ot = uops->sum * 1.0;
		un = unhalt->sum * 1.0;
	}
	res = ot/(con * un);
	ret = printf("%1.3f", res);
	return(ret);
}