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
 int /*<<< orphan*/  NAN ; 
 scalar_t__ fpequal (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test (char*,int) ; 

void
run_inf_opt_test(double d)
{

	test("optimizations don't break infinities",
	     fpequal(d / d, NAN) && fpequal(0.0 * d, NAN));
}