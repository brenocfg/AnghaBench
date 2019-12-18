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
 double SQRT_MIN ; 

__attribute__((used)) static inline double
sum_squares(double x, double y)
{

	/* Avoid underflow when y is small. */
	if (y < SQRT_MIN)
		return (x * x);

	return (x * x + y * y);
}