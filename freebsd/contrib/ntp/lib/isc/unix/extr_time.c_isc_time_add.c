#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nanoseconds; scalar_t__ seconds; } ;
typedef  TYPE_1__ isc_time_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_7__ {scalar_t__ nanoseconds; scalar_t__ seconds; } ;
typedef  TYPE_2__ isc_interval_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  ISC_R_RANGE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 scalar_t__ NS_PER_S ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ UINT_MAX ; 

isc_result_t
isc_time_add(const isc_time_t *t, const isc_interval_t *i, isc_time_t *result)
{
	REQUIRE(t != NULL && i != NULL && result != NULL);
	INSIST(t->nanoseconds < NS_PER_S && i->nanoseconds < NS_PER_S);

	/*
	 * Ensure the resulting seconds value fits in the size of an
	 * unsigned int.  (It is written this way as a slight optimization;
	 * note that even if both values == INT_MAX, then when added
	 * and getting another 1 added below the result is UINT_MAX.)
	 */
	if ((t->seconds > INT_MAX || i->seconds > INT_MAX) &&
	    ((long long)t->seconds + i->seconds > UINT_MAX))
		return (ISC_R_RANGE);

	result->seconds = t->seconds + i->seconds;
	result->nanoseconds = t->nanoseconds + i->nanoseconds;
	if (result->nanoseconds >= NS_PER_S) {
		result->seconds++;
		result->nanoseconds -= NS_PER_S;
	}

	return (ISC_R_SUCCESS);
}