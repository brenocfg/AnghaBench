#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct cpumask {int dummy; } ;
struct rdtgroup {scalar_t__ mode; struct cpumask cpu_mask; TYPE_2__* plr; } ;
struct kernfs_open_file {int /*<<< orphan*/  kn; } ;
struct TYPE_4__ {TYPE_1__* d; } ;
struct TYPE_3__ {struct cpumask cpu_mask; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 scalar_t__ RDT_MODE_PSEUDO_LOCKED ; 
 int /*<<< orphan*/  cpumask_pr_args (struct cpumask*) ; 
 scalar_t__ is_cpu_list (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  rdt_last_cmd_clear () ; 
 int /*<<< orphan*/  rdt_last_cmd_puts (char*) ; 
 struct rdtgroup* rdtgroup_kn_lock_live (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdtgroup_kn_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdtgroup_cpus_show(struct kernfs_open_file *of,
			      struct seq_file *s, void *v)
{
	struct rdtgroup *rdtgrp;
	struct cpumask *mask;
	int ret = 0;

	rdtgrp = rdtgroup_kn_lock_live(of->kn);

	if (rdtgrp) {
		if (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED) {
			if (!rdtgrp->plr->d) {
				rdt_last_cmd_clear();
				rdt_last_cmd_puts("Cache domain offline\n");
				ret = -ENODEV;
			} else {
				mask = &rdtgrp->plr->d->cpu_mask;
				seq_printf(s, is_cpu_list(of) ?
					   "%*pbl\n" : "%*pb\n",
					   cpumask_pr_args(mask));
			}
		} else {
			seq_printf(s, is_cpu_list(of) ? "%*pbl\n" : "%*pb\n",
				   cpumask_pr_args(&rdtgrp->cpu_mask));
		}
	} else {
		ret = -ENOENT;
	}
	rdtgroup_kn_unlock(of->kn);

	return ret;
}