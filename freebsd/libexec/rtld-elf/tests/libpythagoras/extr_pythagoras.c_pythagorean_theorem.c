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
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ pow (double,int) ; 
 double sqrt (scalar_t__) ; 

double
pythagorean_theorem(double a, double b)
{

	if (a <= 0 || b <= 0) {
		errno = ERANGE;
		return (-1.0);
	}
	return (sqrt(pow(a, 2) + pow(b, 2)));
}