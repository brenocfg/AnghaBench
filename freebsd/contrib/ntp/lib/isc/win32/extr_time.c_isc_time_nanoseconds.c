#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int isc_uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
struct TYPE_6__ {TYPE_1__ absolute; } ;
typedef  TYPE_2__ isc_time_t ;
struct TYPE_7__ {int QuadPart; int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  TYPE_3__ ULARGE_INTEGER ;

/* Variables and functions */

isc_uint32_t
isc_time_nanoseconds(const isc_time_t *t) {
	ULARGE_INTEGER i;

	i.LowPart  = t->absolute.dwLowDateTime;
	i.HighPart = t->absolute.dwHighDateTime;
	return ((isc_uint32_t)(i.QuadPart % 10000000) * 100);
}