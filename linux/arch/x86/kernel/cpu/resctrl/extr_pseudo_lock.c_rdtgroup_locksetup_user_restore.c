#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rdtgroup {int dummy; } ;

/* Variables and functions */
 scalar_t__ rdt_mon_capable ; 
 int rdtgroup_kn_mode_restore (struct rdtgroup*,char*,int) ; 
 int /*<<< orphan*/  rdtgroup_kn_mode_restrict (struct rdtgroup*,char*) ; 

__attribute__((used)) static int rdtgroup_locksetup_user_restore(struct rdtgroup *rdtgrp)
{
	int ret;

	ret = rdtgroup_kn_mode_restore(rdtgrp, "tasks", 0777);
	if (ret)
		return ret;

	ret = rdtgroup_kn_mode_restore(rdtgrp, "cpus", 0777);
	if (ret)
		goto err_tasks;

	ret = rdtgroup_kn_mode_restore(rdtgrp, "cpus_list", 0777);
	if (ret)
		goto err_cpus;

	if (rdt_mon_capable) {
		ret = rdtgroup_kn_mode_restore(rdtgrp, "mon_groups", 0777);
		if (ret)
			goto err_cpus_list;
	}

	ret = 0;
	goto out;

err_cpus_list:
	rdtgroup_kn_mode_restrict(rdtgrp, "cpus_list");
err_cpus:
	rdtgroup_kn_mode_restrict(rdtgrp, "cpus");
err_tasks:
	rdtgroup_kn_mode_restrict(rdtgrp, "tasks");
out:
	return ret;
}