#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct auth_xfer {TYPE_1__* task_probe; } ;
struct TYPE_2__ {scalar_t__ lookup_aaaa; int /*<<< orphan*/  masters; int /*<<< orphan*/  lookup_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfr_masterlist_free_addrs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfr_probe_start_lookups(struct auth_xfer* xfr)
{
	/* delete all the looked up addresses in the list */
	xfr_masterlist_free_addrs(xfr->task_probe->masters);

	/* start lookup at the first master */
	xfr->task_probe->lookup_target = xfr->task_probe->masters;
	xfr->task_probe->lookup_aaaa = 0;
}