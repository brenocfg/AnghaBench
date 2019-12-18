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
 int FE_INVALID ; 
 double INFINITY ; 
 double NAN ; 
 double* finites ; 
 unsigned int nitems (double*) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int /*<<< orphan*/  testall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
test_nan(void)
{
	unsigned i;

	/* cexp(x + NaNi) = NaN + NaNi and optionally raises invalid */
	/* cexp(NaN + yi) = NaN + NaNi and optionally raises invalid (|y|>0) */
	for (i = 0; i < nitems(finites); i++) {
		printf("# Run %d..\n", i);
		testall(CMPLXL(finites[i], NAN), CMPLXL(NAN, NAN),
			ALL_STD_EXCEPT & ~FE_INVALID, 0, 0);
		if (finites[i] == 0.0)
			continue;
		/* XXX FE_INEXACT shouldn't be raised here */
		testall(CMPLXL(NAN, finites[i]), CMPLXL(NAN, NAN),
			ALL_STD_EXCEPT & ~(FE_INVALID | FE_INEXACT), 0, 0);
	}

	/* cexp(NaN +- 0i) = NaN +- 0i */
	testall(CMPLXL(NAN, 0.0), CMPLXL(NAN, 0.0), ALL_STD_EXCEPT, 0, 1);
	testall(CMPLXL(NAN, -0.0), CMPLXL(NAN, -0.0), ALL_STD_EXCEPT, 0, 1);

	/* cexp(inf + NaN i) = inf + nan i */
	testall(CMPLXL(INFINITY, NAN), CMPLXL(INFINITY, NAN),
		ALL_STD_EXCEPT, 0, 0);
	/* cexp(-inf + NaN i) = 0 */
	testall(CMPLXL(-INFINITY, NAN), CMPLXL(0.0, 0.0),
		ALL_STD_EXCEPT, 0, 0);
	/* cexp(NaN + NaN i) = NaN + NaN i */
	testall(CMPLXL(NAN, NAN), CMPLXL(NAN, NAN),
		ALL_STD_EXCEPT, 0, 0);
}