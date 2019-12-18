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
 double DBL_EPSILON ; 
 int FE_DOWNWARD ; 
 int FE_TONEAREST ; 
 int FE_TOWARDZERO ; 
 int FE_UPWARD ; 
 double copysign (double,double volatile) ; 

__attribute__((used)) static int
getround(void)
{
	volatile double d;

	/*
	 * This test works just as well with 0.0 - 0.0, except on ia64
	 * where 0.0 - 0.0 gives the wrong sign when rounding downwards.
	 */
	d = 1.0;
	d -= 1.0;
	if (copysign(1.0, d) < 0.0)
		return (FE_DOWNWARD);

	d = 1.0;
	if (d + (DBL_EPSILON * 3.0 / 4.0) == 1.0)
		return (FE_TOWARDZERO);
	if (d + (DBL_EPSILON * 1.0 / 4.0) > 1.0)
		return (FE_UPWARD);

	return (FE_TONEAREST);
}