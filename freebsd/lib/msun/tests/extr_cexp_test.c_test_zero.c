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
 int /*<<< orphan*/  ALL_STD_EXCEPT ; 
 double CMPLXL (double,double) ; 
 int /*<<< orphan*/  testall (double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
test_zero(void)
{

	/* cexp(0) = 1, no exceptions raised */
	testall(0.0, 1.0, ALL_STD_EXCEPT, 0, 1);
	testall(-0.0, 1.0, ALL_STD_EXCEPT, 0, 1);
	testall(CMPLXL(0.0, -0.0), CMPLXL(1.0, -0.0), ALL_STD_EXCEPT, 0, 1);
	testall(CMPLXL(-0.0, -0.0), CMPLXL(1.0, -0.0), ALL_STD_EXCEPT, 0, 1);
}