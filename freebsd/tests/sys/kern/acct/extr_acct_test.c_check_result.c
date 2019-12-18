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
union cf {float f; double c; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK (int) ; 
 double FLT_EPSILON ; 
 float fabs (float) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
check_result(const char *name, float expected, union cf v)
{
	double eps;

	eps = fabs(expected - v.f) / expected;
	ATF_CHECK(eps <= FLT_EPSILON);
	if (eps > FLT_EPSILON) {
		printf("Error in %s\n", name);
		printf("Got      0x%08x %12g\n", v.c, v.f);
		v.f = expected;
		printf("Expected 0x%08x %12g (%.15lg)\n", v.c, v.f, expected);
		printf("Epsilon=%lg, rather than %g\n", eps, FLT_EPSILON);
	}
}