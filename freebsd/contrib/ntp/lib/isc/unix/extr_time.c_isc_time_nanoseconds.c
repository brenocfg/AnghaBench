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
typedef  int /*<<< orphan*/  isc_uint32_t ;
struct TYPE_3__ {scalar_t__ nanoseconds; } ;
typedef  TYPE_1__ isc_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENSURE (int) ; 
 scalar_t__ NS_PER_S ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 

isc_uint32_t
isc_time_nanoseconds(const isc_time_t *t) {
	REQUIRE(t != NULL);

	ENSURE(t->nanoseconds < NS_PER_S);

	return ((isc_uint32_t)t->nanoseconds);
}