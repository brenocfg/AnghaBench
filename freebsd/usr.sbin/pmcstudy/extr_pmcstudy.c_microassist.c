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
microassist(struct counters *cpu, int pos)
{
	/* 14  - IDQ.MS_CYCLES / CPU_CLK_UNHALTED.THREAD_P (thresh > .05) */
	int ret;
	struct counters *idq;
	struct counters *unhalt;
	double un, id, res, con;

	con = 4.0;
	unhalt = find_counter(cpu, "CPU_CLK_UNHALTED.THREAD_P");
	idq = find_counter(cpu, "IDQ.MS_UOPS");
	if (pos != -1) {
		id = idq->vals[pos] * 1.0;
		un = unhalt->vals[pos] * 1.0;
	} else {
		id = idq->sum * 1.0;
		un = unhalt->sum * 1.0;
	}
	res = id/(un * con);
	ret = printf("%1.3f", res);
	return(ret);
}