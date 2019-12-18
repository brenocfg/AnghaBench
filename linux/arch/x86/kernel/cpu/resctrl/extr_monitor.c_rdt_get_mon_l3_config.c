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
struct rdt_resource {unsigned int mon_scale; unsigned int num_rmid; int mon_capable; int mon_enabled; } ;
struct TYPE_2__ {unsigned int x86_cache_size; unsigned int x86_cache_occ_scale; unsigned int x86_cache_max_rmid; } ;

/* Variables and functions */
 TYPE_1__ boot_cpu_data ; 
 int dom_data_init (struct rdt_resource*) ; 
 int /*<<< orphan*/  l3_mon_evt_init (struct rdt_resource*) ; 
 unsigned int resctrl_cqm_threshold ; 

int rdt_get_mon_l3_config(struct rdt_resource *r)
{
	unsigned int cl_size = boot_cpu_data.x86_cache_size;
	int ret;

	r->mon_scale = boot_cpu_data.x86_cache_occ_scale;
	r->num_rmid = boot_cpu_data.x86_cache_max_rmid + 1;

	/*
	 * A reasonable upper limit on the max threshold is the number
	 * of lines tagged per RMID if all RMIDs have the same number of
	 * lines tagged in the LLC.
	 *
	 * For a 35MB LLC and 56 RMIDs, this is ~1.8% of the LLC.
	 */
	resctrl_cqm_threshold = cl_size * 1024 / r->num_rmid;

	/* h/w works in units of "boot_cpu_data.x86_cache_occ_scale" */
	resctrl_cqm_threshold /= r->mon_scale;

	ret = dom_data_init(r);
	if (ret)
		return ret;

	l3_mon_evt_init(r);

	r->mon_capable = true;
	r->mon_enabled = true;

	return 0;
}