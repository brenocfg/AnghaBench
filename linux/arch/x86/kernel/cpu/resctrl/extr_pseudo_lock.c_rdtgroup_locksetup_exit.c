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
struct TYPE_2__ {int rmid; } ;
struct rdtgroup {TYPE_1__ mon; } ;

/* Variables and functions */
 int alloc_rmid () ; 
 int /*<<< orphan*/  free_rmid (int) ; 
 int /*<<< orphan*/  pseudo_lock_free (struct rdtgroup*) ; 
 int /*<<< orphan*/  rdt_last_cmd_puts (char*) ; 
 scalar_t__ rdt_mon_capable ; 
 int rdtgroup_locksetup_user_restore (struct rdtgroup*) ; 

int rdtgroup_locksetup_exit(struct rdtgroup *rdtgrp)
{
	int ret;

	if (rdt_mon_capable) {
		ret = alloc_rmid();
		if (ret < 0) {
			rdt_last_cmd_puts("Out of RMIDs\n");
			return ret;
		}
		rdtgrp->mon.rmid = ret;
	}

	ret = rdtgroup_locksetup_user_restore(rdtgrp);
	if (ret) {
		free_rmid(rdtgrp->mon.rmid);
		return ret;
	}

	pseudo_lock_free(rdtgrp);
	return 0;
}