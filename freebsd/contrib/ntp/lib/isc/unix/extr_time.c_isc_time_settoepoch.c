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
struct TYPE_3__ {scalar_t__ nanoseconds; scalar_t__ seconds; } ;
typedef  TYPE_1__ isc_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 

void
isc_time_settoepoch(isc_time_t *t) {
	REQUIRE(t != NULL);

	t->seconds = 0;
	t->nanoseconds = 0;
}