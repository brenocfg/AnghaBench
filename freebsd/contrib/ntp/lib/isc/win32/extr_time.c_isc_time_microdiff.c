#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int isc_uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
struct TYPE_7__ {TYPE_1__ absolute; } ;
typedef  TYPE_2__ isc_time_t ;
struct TYPE_8__ {scalar_t__ QuadPart; int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  TYPE_3__ ULARGE_INTEGER ;
typedef  int LONGLONG ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 

isc_uint64_t
isc_time_microdiff(const isc_time_t *t1, const isc_time_t *t2) {
	ULARGE_INTEGER i1, i2;
	LONGLONG i3;

	REQUIRE(t1 != NULL && t2 != NULL);

	i1.LowPart  = t1->absolute.dwLowDateTime;
	i1.HighPart = t1->absolute.dwHighDateTime;
	i2.LowPart  = t2->absolute.dwLowDateTime;
	i2.HighPart = t2->absolute.dwHighDateTime;

	if (i1.QuadPart <= i2.QuadPart)
		return (0);

	/*
	 * Convert to microseconds.
	 */
	i3 = (i1.QuadPart - i2.QuadPart) / 10;

	return (i3);
}