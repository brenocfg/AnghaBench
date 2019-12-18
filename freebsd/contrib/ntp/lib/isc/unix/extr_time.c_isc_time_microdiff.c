#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_uint64_t ;
struct TYPE_4__ {scalar_t__ nanoseconds; scalar_t__ seconds; } ;
typedef  TYPE_1__ isc_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ NS_PER_S ; 
 scalar_t__ NS_PER_US ; 
 int /*<<< orphan*/  REQUIRE (int) ; 

isc_uint64_t
isc_time_microdiff(const isc_time_t *t1, const isc_time_t *t2) {
	isc_uint64_t i1, i2, i3;

	REQUIRE(t1 != NULL && t2 != NULL);
	INSIST(t1->nanoseconds < NS_PER_S && t2->nanoseconds < NS_PER_S);

	i1 = (isc_uint64_t)t1->seconds * NS_PER_S + t1->nanoseconds;
	i2 = (isc_uint64_t)t2->seconds * NS_PER_S + t2->nanoseconds;

	if (i1 <= i2)
		return (0);

	i3 = i1 - i2;

	/*
	 * Convert to microseconds.
	 */
	i3 /= NS_PER_US;

	return (i3);
}