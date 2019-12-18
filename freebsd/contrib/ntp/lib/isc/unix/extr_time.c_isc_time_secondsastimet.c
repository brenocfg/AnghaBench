#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  isc_uint32_t ;
struct TYPE_3__ {scalar_t__ nanoseconds; unsigned int seconds; } ;
typedef  TYPE_1__ isc_time_t ;
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_R_RANGE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 scalar_t__ NS_PER_S ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 

isc_result_t
isc_time_secondsastimet(const isc_time_t *t, time_t *secondsp) {
	time_t seconds;

	REQUIRE(t != NULL);
	INSIST(t->nanoseconds < NS_PER_S);

	/*
	 * Ensure that the number of seconds represented by t->seconds
	 * can be represented by a time_t.  Since t->seconds is an unsigned
	 * int and since time_t is mostly opaque, this is trickier than
	 * it seems.  (This standardized opaqueness of time_t is *very*
	 * frustrating; time_t is not even limited to being an integral
	 * type.)
	 *
	 * The mission, then, is to avoid generating any kind of warning
	 * about "signed versus unsigned" while trying to determine if the
	 * the unsigned int t->seconds is out range for tv_sec, which is
	 * pretty much only true if time_t is a signed integer of the same
	 * size as the return value of isc_time_seconds.
	 *
	 * If the paradox in the if clause below is true, t->seconds is out
	 * of range for time_t.
	 */
	seconds = (time_t)t->seconds;

	INSIST(sizeof(unsigned int) == sizeof(isc_uint32_t));
	INSIST(sizeof(time_t) >= sizeof(isc_uint32_t));

	if (t->seconds > (~0U>>1) && seconds <= (time_t)(~0U>>1))
		return (ISC_R_RANGE);

	*secondsp = seconds;

	return (ISC_R_SUCCESS);
}