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
typedef  int /*<<< orphan*/  zeroi ;
typedef  int u_int8_t ;
struct rndtest_state {int* rs_buf; } ;
typedef  int /*<<< orphan*/  onei ;
struct TYPE_2__ {int /*<<< orphan*/  rst_runs; } ;

/* Variables and functions */
 int RNDTEST_NBYTES ; 
 int RNDTEST_RUNS_NINTERVAL ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 TYPE_1__ rndstats ; 
 int rndtest_runs_check (struct rndtest_state*,int,int*) ; 
 int /*<<< orphan*/  rndtest_runs_record (struct rndtest_state*,int,int*) ; 

__attribute__((used)) static int
rndtest_runs(struct rndtest_state *rsp)
{
	int i, j, ones, zeros, rv = 0;
	int onei[RNDTEST_RUNS_NINTERVAL], zeroi[RNDTEST_RUNS_NINTERVAL];
	u_int8_t c;

	bzero(onei, sizeof(onei));
	bzero(zeroi, sizeof(zeroi));
	ones = zeros = 0;
	for (i = 0; i < RNDTEST_NBYTES; i++) {
		c = rsp->rs_buf[i];
		for (j = 0; j < 8; j++, c <<= 1) {
			if (c & 0x80) {
				ones++;
				rndtest_runs_record(rsp, zeros, zeroi);
				zeros = 0;
			} else {
				zeros++;
				rndtest_runs_record(rsp, ones, onei);
				ones = 0;
			}
		}
	}
	rndtest_runs_record(rsp, ones, onei);
	rndtest_runs_record(rsp, zeros, zeroi);

	rv |= rndtest_runs_check(rsp, 0, zeroi);
	rv |= rndtest_runs_check(rsp, 1, onei);

	if (rv)
		rndstats.rst_runs++;

	return (rv);
}