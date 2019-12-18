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
typedef  int /*<<< orphan*/  isc_boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  due; } ;
typedef  TYPE_1__ isc__timer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_TIMER (TYPE_1__*) ; 
 scalar_t__ isc_time_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static isc_boolean_t
sooner(void *v1, void *v2) {
	isc__timer_t *t1, *t2;

	t1 = v1;
	t2 = v2;
	REQUIRE(VALID_TIMER(t1));
	REQUIRE(VALID_TIMER(t2));

	if (isc_time_compare(&t1->due, &t2->due) < 0)
		return (ISC_TRUE);
	return (ISC_FALSE);
}