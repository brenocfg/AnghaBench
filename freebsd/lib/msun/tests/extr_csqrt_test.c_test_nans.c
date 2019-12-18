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
 int /*<<< orphan*/  CMPLXL (double,double) ; 
 double INFINITY ; 
 double NAN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double cimagl (int /*<<< orphan*/ ) ; 
 double creall (int /*<<< orphan*/ ) ; 
 int isinf (double) ; 
 int isnan (double) ; 
 int /*<<< orphan*/  t_csqrt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_nans(void)
{

	assert(creall(t_csqrt(CMPLXL(INFINITY, NAN))) == INFINITY);
	assert(isnan(cimagl(t_csqrt(CMPLXL(INFINITY, NAN)))));

	assert(isnan(creall(t_csqrt(CMPLXL(-INFINITY, NAN)))));
	assert(isinf(cimagl(t_csqrt(CMPLXL(-INFINITY, NAN)))));

	assert_equal(t_csqrt(CMPLXL(NAN, INFINITY)),
		     CMPLXL(INFINITY, INFINITY));
	assert_equal(t_csqrt(CMPLXL(NAN, -INFINITY)),
		     CMPLXL(INFINITY, -INFINITY));

	assert_equal(t_csqrt(CMPLXL(0.0, NAN)), CMPLXL(NAN, NAN));
	assert_equal(t_csqrt(CMPLXL(-0.0, NAN)), CMPLXL(NAN, NAN));
	assert_equal(t_csqrt(CMPLXL(42.0, NAN)), CMPLXL(NAN, NAN));
	assert_equal(t_csqrt(CMPLXL(-42.0, NAN)), CMPLXL(NAN, NAN));
	assert_equal(t_csqrt(CMPLXL(NAN, 0.0)), CMPLXL(NAN, NAN));
	assert_equal(t_csqrt(CMPLXL(NAN, -0.0)), CMPLXL(NAN, NAN));
	assert_equal(t_csqrt(CMPLXL(NAN, 42.0)), CMPLXL(NAN, NAN));
	assert_equal(t_csqrt(CMPLXL(NAN, -42.0)), CMPLXL(NAN, NAN));
	assert_equal(t_csqrt(CMPLXL(NAN, NAN)), CMPLXL(NAN, NAN));
}