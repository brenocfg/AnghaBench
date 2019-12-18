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
typedef  int time_t ;
struct timespec {int tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_SECOND ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 

time_t
time(time_t *t)
{
	struct timespec tt;
	time_t retval;

	if (clock_gettime(CLOCK_SECOND, &tt) < 0)
		retval = -1;
	else
		retval = tt.tv_sec;
	if (t != NULL)
		*t = retval;
	return (retval);
}