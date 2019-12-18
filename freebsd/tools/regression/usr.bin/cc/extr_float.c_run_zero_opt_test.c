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

/* Variables and functions */
 scalar_t__ fpequal (double,double) ; 
 int /*<<< orphan*/  test (char*,int) ; 

void
run_zero_opt_test(double d1, double d2)
{

	test("optimizations don't break the sign of 0",
	     fpequal(d1 - d2, 0.0)
	     && fpequal(-d1 + 0.0, 0.0)
	     && fpequal(-d1 - d2, -0.0)
	     && fpequal(-(d1 - d2), -0.0)
	     && fpequal(-d1 - (-d2), 0.0));
}