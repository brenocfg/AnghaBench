#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
struct TYPE_10__ {TYPE_1__ absolute; } ;
typedef  TYPE_2__ isc_time_t ;
struct TYPE_11__ {int QuadPart; int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  TYPE_3__ ULARGE_INTEGER ;
struct TYPE_13__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
struct TYPE_12__ {int member_0; int member_1; int member_2; int member_3; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; } ;
typedef  TYPE_4__ SYSTEMTIME ;
typedef  int LONGLONG ;
typedef  TYPE_5__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  SystemTimeToFileTime (TYPE_4__*,TYPE_5__*) ; 

isc_uint32_t
isc_time_seconds(const isc_time_t *t) {
	SYSTEMTIME epoch = { 1970, 1, 4, 1, 0, 0, 0, 0 };
	FILETIME temp;
	ULARGE_INTEGER i1, i2;
	LONGLONG i3;

	SystemTimeToFileTime(&epoch, &temp);

	i1.LowPart  = t->absolute.dwLowDateTime;
	i1.HighPart = t->absolute.dwHighDateTime;
	i2.LowPart  = temp.dwLowDateTime;
	i2.HighPart = temp.dwHighDateTime;

	i3 = (i1.QuadPart - i2.QuadPart) / 10000000;

	return ((isc_uint32_t)i3);
}