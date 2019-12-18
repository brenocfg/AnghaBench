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
 scalar_t__ CMPLXL (double,double) ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int nitems (double const*) ; 
 scalar_t__ t_csqrt (scalar_t__) ; 

__attribute__((used)) static void
test_finite(void)
{
	static const double tests[] = {
	     /* csqrt(a + bI) = x + yI */
	     /* a	b	x	y */
		0,	8,	2,	2,
		0,	-8,	2,	-2,
		4,	0,	2,	0,
		-4,	0,	0,	2,
		3,	4,	2,	1,
		3,	-4,	2,	-1,
		-3,	4,	1,	2,
		-3,	-4,	1,	-2,
		5,	12,	3,	2,
		7,	24,	4,	3,
		9,	40,	5,	4,
		11,	60,	6,	5,
		13,	84,	7,	6,
		33,	56,	7,	4,
		39,	80,	8,	5,
		65,	72,	9,	4,
		987,	9916,	74,	67,
		5289,	6640,	83,	40,
		460766389075.0, 16762287900.0, 678910, 12345
	};
	/*
	 * We also test some multiples of the above arguments. This
	 * array defines which multiples we use. Note that these have
	 * to be small enough to not cause overflow for float precision
	 * with all of the constants in the above table.
	 */
	static const double mults[] = {
		1,
		2,
		3,
		13,
		16,
		0x1.p30,
		0x1.p-30,
	};

	double a, b;
	double x, y;
	unsigned i, j;

	for (i = 0; i < nitems(tests); i += 4) {
		for (j = 0; j < nitems(mults); j++) {
			a = tests[i] * mults[j] * mults[j];
			b = tests[i + 1] * mults[j] * mults[j];
			x = tests[i + 2] * mults[j];
			y = tests[i + 3] * mults[j];
			assert(t_csqrt(CMPLXL(a, b)) == CMPLXL(x, y));
		}
	}

}