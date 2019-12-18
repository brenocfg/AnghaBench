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
struct TYPE_2__ {int /*<<< orphan*/  rst_longruns; } ;

/* Variables and functions */
 int RNDTEST_NBYTES ; 
 TYPE_1__ rndstats ; 
 int /*<<< orphan*/  rndtest_report (struct rndtest_state*,int,char*,int,int) ; 

__attribute__((used)) static int
rndtest_longruns(struct rndtest_state *rsp)
{
	int i, j, ones = 0, zeros = 0, maxones = 0, maxzeros = 0;
	u_int8_t c;

	for (i = 0; i < RNDTEST_NBYTES; i++) {
		c = rsp->rs_buf[i];
		for (j = 0; j < 8; j++, c <<= 1) {
			if (c & 0x80) {
				zeros = 0;
				ones++;
				if (ones > maxones)
					maxones = ones;
			} else {
				ones = 0;
				zeros++;
				if (zeros > maxzeros)
					maxzeros = zeros;
			}
		}
	}

	if (maxones < 26 && maxzeros < 26) {
		rndtest_report(rsp, 0, "longruns pass (%d ones, %d zeros)",
			maxones, maxzeros);
		return (0);
	} else {
		rndtest_report(rsp, 1, "longruns fail (%d ones, %d zeros)",
			maxones, maxzeros);
		rndstats.rst_longruns++;
		return (-1);
	}
}