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
 int /*<<< orphan*/  assert_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t_csqrt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_zeros(void)
{

	assert_equal(t_csqrt(CMPLXL(0.0, 0.0)), CMPLXL(0.0, 0.0));
	assert_equal(t_csqrt(CMPLXL(-0.0, 0.0)), CMPLXL(0.0, 0.0));
	assert_equal(t_csqrt(CMPLXL(0.0, -0.0)), CMPLXL(0.0, -0.0));
	assert_equal(t_csqrt(CMPLXL(-0.0, -0.0)), CMPLXL(0.0, -0.0));
}