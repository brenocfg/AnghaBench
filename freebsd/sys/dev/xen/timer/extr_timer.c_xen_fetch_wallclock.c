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
struct timespec {int dummy; } ;
struct pvclock_wall_clock {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  wc_version; } ;
typedef  TYPE_1__ shared_info_t ;

/* Variables and functions */
 TYPE_1__* HYPERVISOR_shared_info ; 
 int /*<<< orphan*/  pvclock_get_wallclock (struct pvclock_wall_clock*,struct timespec*) ; 

__attribute__((used)) static void
xen_fetch_wallclock(struct timespec *ts)
{
	shared_info_t *src = HYPERVISOR_shared_info;
	struct pvclock_wall_clock *wc;

	wc = (struct pvclock_wall_clock *) &src->wc_version;

	pvclock_get_wallclock(wc, ts);
}