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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 scalar_t__ leapcorr (scalar_t__*) ; 
 int /*<<< orphan*/  tzset () ; 

time_t
posix2time(time_t t)
{
	time_t	x;
	time_t	y;

	tzset();
	/*
	** For a positive leap second hit, the result
	** is not unique. For a negative leap second
	** hit, the corresponding time doesn't exist,
	** so we return an adjacent second.
	*/
	x = t + leapcorr(&t);
	y = x - leapcorr(&x);
	if (y < t) {
		do {
			x++;
			y = x - leapcorr(&x);
		} while (y < t);
		if (t != y)
			return x - 1;
	} else if (y > t) {
		do {
			--x;
			y = x - leapcorr(&x);
		} while (y > t);
		if (t != y)
			return x + 1;
	}
	return x;
}