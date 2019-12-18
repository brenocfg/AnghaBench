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
struct TYPE_4__ {scalar_t__ nanoseconds; scalar_t__ seconds; } ;
typedef  TYPE_1__ isc_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ NS_PER_S ; 
 int /*<<< orphan*/  REQUIRE (int) ; 

int
isc_time_compare(const isc_time_t *t1, const isc_time_t *t2) {
	REQUIRE(t1 != NULL && t2 != NULL);
	INSIST(t1->nanoseconds < NS_PER_S && t2->nanoseconds < NS_PER_S);

	if (t1->seconds < t2->seconds)
		return (-1);
	if (t1->seconds > t2->seconds)
		return (1);
	if (t1->nanoseconds < t2->nanoseconds)
		return (-1);
	if (t1->nanoseconds > t2->nanoseconds)
		return (1);
	return (0);
}