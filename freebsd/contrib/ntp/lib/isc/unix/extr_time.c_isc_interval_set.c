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
struct TYPE_3__ {unsigned int seconds; unsigned int nanoseconds; } ;
typedef  TYPE_1__ isc_interval_t ;

/* Variables and functions */
 unsigned int NS_PER_S ; 
 int /*<<< orphan*/  REQUIRE (int) ; 

void
isc_interval_set(isc_interval_t *i,
		 unsigned int seconds, unsigned int nanoseconds)
{
	REQUIRE(i != NULL);
	REQUIRE(nanoseconds < NS_PER_S);

	i->seconds = seconds;
	i->nanoseconds = nanoseconds;
}