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
typedef  scalar_t__ uintmax_t ;
typedef  int timestamp_t ;
typedef  int time_t ;

/* Variables and functions */
 scalar_t__ TIME_MAX ; 

int date_overflows(timestamp_t t)
{
	time_t sys;

	/* If we overflowed our timestamp data type, that's bad... */
	if ((uintmax_t)t >= TIME_MAX)
		return 1;

	/*
	 * ...but we also are going to feed the result to system
	 * functions that expect time_t, which is often "signed long".
	 * Make sure that we fit into time_t, as well.
	 */
	sys = t;
	return t != sys || (t < 1) != (sys < 1);
}