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
struct rndtest_state {int dummy; } ;
struct TYPE_2__ {int min; int max; } ;

/* Variables and functions */
 int RNDTEST_RUNS_NINTERVAL ; 
 int /*<<< orphan*/  rndtest_report (struct rndtest_state*,int,char*,char*,int,int,int,int) ; 
 TYPE_1__* rndtest_runs_tab ; 

__attribute__((used)) static int
rndtest_runs_check(struct rndtest_state *rsp, int val, int *src)
{
	int i, rv = 0;

	for (i = 0; i < RNDTEST_RUNS_NINTERVAL; i++) {
		if (src[i] < rndtest_runs_tab[i].min ||
		    src[i] > rndtest_runs_tab[i].max) {
			rndtest_report(rsp, 1,
			    "%s interval %d failed (%d, %d-%d)",
			    val ? "ones" : "zeros",
			    i + 1, src[i], rndtest_runs_tab[i].min,
			    rndtest_runs_tab[i].max);
			rv = -1;
		} else {
			rndtest_report(rsp, 0,
			    "runs pass %s interval %d (%d < %d < %d)",
			    val ? "ones" : "zeros",
			    i + 1, rndtest_runs_tab[i].min, src[i],
			    rndtest_runs_tab[i].max);
		}
	}
	return (rv);
}