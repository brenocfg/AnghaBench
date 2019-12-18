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
blockstoreforward(struct counters *cpu, int pos)
{
        /*  7  - (LD_BLOCKS_STORE_FORWARD * 13) / CPU_CLK_UNHALTED.THREAD_P (thresh >= .05)*/
	int ret;
	struct counters *ldb;
	struct counters *unhalt;
	double con, un, ld, res;

	con = 13.0;
	unhalt = find_counter(cpu, "CPU_CLK_UNHALTED.THREAD_P");
	ldb = find_counter(cpu, "LD_BLOCKS_STORE_FORWARD");
	if (pos != -1) {
		ld = ldb->vals[pos] * 1.0;
		un = unhalt->vals[pos] * 1.0;
	} else {
		ld = ldb->sum * 1.0;
		un = unhalt->sum * 1.0;
	}
	res = (ld * con)/un;
	ret = printf("%1.3f", res);
	return(ret);
}