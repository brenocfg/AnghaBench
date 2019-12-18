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
 int ALL_STD_EXCEPT ; 
 int /*<<< orphan*/  CMPLXL (double,double) ; 
 int FE_INEXACT ; 
 int /*<<< orphan*/  FE_INVALID ; 
 double INFINITY ; 
 int M_PI_4 ; 
 double NAN ; 
 double* finites ; 
 unsigned int nitems (double*) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int /*<<< orphan*/  testall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
test_inf(void)
{
	unsigned i;

	/* cexp(x + inf i) = NaN + NaNi and raises invalid */
	for (i = 0; i < nitems(finites); i++) {
		printf("# Run %d..\n", i);
		testall(CMPLXL(finites[i], INFINITY), CMPLXL(NAN, NAN),
			ALL_STD_EXCEPT, FE_INVALID, 1);
	}
	/* cexp(-inf + yi) = 0 * (cos(y) + sin(y)i) */
	/* XXX shouldn't raise an inexact exception */
	testall(CMPLXL(-INFINITY, M_PI_4), CMPLXL(0.0, 0.0),
		ALL_STD_EXCEPT & ~FE_INEXACT, 0, 1);
	testall(CMPLXL(-INFINITY, 3 * M_PI_4), CMPLXL(-0.0, 0.0),
		ALL_STD_EXCEPT & ~FE_INEXACT, 0, 1);
	testall(CMPLXL(-INFINITY, 5 * M_PI_4), CMPLXL(-0.0, -0.0),
		ALL_STD_EXCEPT & ~FE_INEXACT, 0, 1);
	testall(CMPLXL(-INFINITY, 7 * M_PI_4), CMPLXL(0.0, -0.0),
		ALL_STD_EXCEPT & ~FE_INEXACT, 0, 1);
	testall(CMPLXL(-INFINITY, 0.0), CMPLXL(0.0, 0.0),
		ALL_STD_EXCEPT, 0, 1);
	testall(CMPLXL(-INFINITY, -0.0), CMPLXL(0.0, -0.0),
		ALL_STD_EXCEPT, 0, 1);
	/* cexp(inf + yi) = inf * (cos(y) + sin(y)i) (except y=0) */
	/* XXX shouldn't raise an inexact exception */
	testall(CMPLXL(INFINITY, M_PI_4), CMPLXL(INFINITY, INFINITY),
		ALL_STD_EXCEPT & ~FE_INEXACT, 0, 1);
	testall(CMPLXL(INFINITY, 3 * M_PI_4), CMPLXL(-INFINITY, INFINITY),
		ALL_STD_EXCEPT & ~FE_INEXACT, 0, 1);
	testall(CMPLXL(INFINITY, 5 * M_PI_4), CMPLXL(-INFINITY, -INFINITY),
		ALL_STD_EXCEPT & ~FE_INEXACT, 0, 1);
	testall(CMPLXL(INFINITY, 7 * M_PI_4), CMPLXL(INFINITY, -INFINITY),
		ALL_STD_EXCEPT & ~FE_INEXACT, 0, 1);
	/* cexp(inf + 0i) = inf + 0i */
	testall(CMPLXL(INFINITY, 0.0), CMPLXL(INFINITY, 0.0),
		ALL_STD_EXCEPT, 0, 1);
	testall(CMPLXL(INFINITY, -0.0), CMPLXL(INFINITY, -0.0),
		ALL_STD_EXCEPT, 0, 1);
}