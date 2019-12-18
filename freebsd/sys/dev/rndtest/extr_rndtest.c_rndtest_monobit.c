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
typedef  int u_int8_t ;
struct rndtest_state {int* rs_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  rst_monobit; } ;

/* Variables and functions */
 int RNDTEST_MONOBIT_MAXONES ; 
 int RNDTEST_MONOBIT_MINONES ; 
 int RNDTEST_NBYTES ; 
 TYPE_1__ rndstats ; 
 int /*<<< orphan*/  rndtest_report (struct rndtest_state*,int,char*,int,...) ; 
 int rndtest_verbose ; 

__attribute__((used)) static int
rndtest_monobit(struct rndtest_state *rsp)
{
	int i, ones = 0, j;
	u_int8_t r;

	for (i = 0; i < RNDTEST_NBYTES; i++) {
		r = rsp->rs_buf[i];
		for (j = 0; j < 8; j++, r <<= 1)
			if (r & 0x80)
				ones++;
	}
	if (ones > RNDTEST_MONOBIT_MINONES &&
	    ones < RNDTEST_MONOBIT_MAXONES) {
		if (rndtest_verbose > 1)
			rndtest_report(rsp, 0, "monobit pass (%d < %d < %d)",
			    RNDTEST_MONOBIT_MINONES, ones,
			    RNDTEST_MONOBIT_MAXONES);
		return (0);
	} else {
		if (rndtest_verbose)
			rndtest_report(rsp, 1,
			    "monobit failed (%d ones)", ones);
		rndstats.rst_monobit++;
		return (-1);
	}
}