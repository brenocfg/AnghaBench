#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dwLowDateTime; scalar_t__ dwHighDateTime; } ;
struct TYPE_5__ {TYPE_1__ absolute; } ;
typedef  TYPE_2__ isc_time_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 

isc_boolean_t
isc_time_isepoch(const isc_time_t *t) {
	REQUIRE(t != NULL);

	if (t->absolute.dwLowDateTime == 0 &&
	    t->absolute.dwHighDateTime == 0)
		return (ISC_TRUE);

	return (ISC_FALSE);
}