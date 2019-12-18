#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pseudo_lock_region {int /*<<< orphan*/  line_size; TYPE_2__* r; int /*<<< orphan*/  cbm; TYPE_3__* d; int /*<<< orphan*/  size; int /*<<< orphan*/  cpu; } ;
struct cpu_cacheinfo {int num_leaves; TYPE_1__* info_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  cpu_mask; } ;
struct TYPE_5__ {scalar_t__ cache_level; } ;
struct TYPE_4__ {scalar_t__ level; int /*<<< orphan*/  coherency_line_size; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cpu_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ *) ; 
 struct cpu_cacheinfo* get_cpu_cacheinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pseudo_lock_region_clear (struct pseudo_lock_region*) ; 
 int /*<<< orphan*/  rdt_last_cmd_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdt_last_cmd_puts (char*) ; 
 int /*<<< orphan*/  rdtgroup_cbm_to_size (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pseudo_lock_region_init(struct pseudo_lock_region *plr)
{
	struct cpu_cacheinfo *ci;
	int ret;
	int i;

	/* Pick the first cpu we find that is associated with the cache. */
	plr->cpu = cpumask_first(&plr->d->cpu_mask);

	if (!cpu_online(plr->cpu)) {
		rdt_last_cmd_printf("CPU %u associated with cache not online\n",
				    plr->cpu);
		ret = -ENODEV;
		goto out_region;
	}

	ci = get_cpu_cacheinfo(plr->cpu);

	plr->size = rdtgroup_cbm_to_size(plr->r, plr->d, plr->cbm);

	for (i = 0; i < ci->num_leaves; i++) {
		if (ci->info_list[i].level == plr->r->cache_level) {
			plr->line_size = ci->info_list[i].coherency_line_size;
			return 0;
		}
	}

	ret = -1;
	rdt_last_cmd_puts("Unable to determine cache line size\n");
out_region:
	pseudo_lock_region_clear(plr);
	return ret;
}