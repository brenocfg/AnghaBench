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
 int /*<<< orphan*/  CMPLXL (double const,double const) ; 
#define  INFINITY 128 
 int /*<<< orphan*/  assert_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double const copysignl (double const,double const) ; 
 scalar_t__ isfinite (double const) ; 
 unsigned int nitems (double const*) ; 
 int /*<<< orphan*/  t_csqrt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_infinities(void)
{
	static const double vals[] = {
		0.0,
		-0.0,
		42.0,
		-42.0,
		INFINITY,
		-INFINITY,
	};

	unsigned i;

	for (i = 0; i < nitems(vals); i++) {
		if (isfinite(vals[i])) {
			assert_equal(t_csqrt(CMPLXL(-INFINITY, vals[i])),
			    CMPLXL(0.0, copysignl(INFINITY, vals[i])));
			assert_equal(t_csqrt(CMPLXL(INFINITY, vals[i])),
			    CMPLXL(INFINITY, copysignl(0.0, vals[i])));
		}
		assert_equal(t_csqrt(CMPLXL(vals[i], INFINITY)),
		    CMPLXL(INFINITY, INFINITY));
		assert_equal(t_csqrt(CMPLXL(vals[i], -INFINITY)),
		    CMPLXL(INFINITY, -INFINITY));
	}
}