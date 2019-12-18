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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct imc_mem_info {int id; int /*<<< orphan*/ * vbase; } ;
struct TYPE_4__ {struct imc_mem_info* mem_info; } ;
struct TYPE_3__ {int id; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  OPAL_IMC_COUNTERS_CORE ; 
 int __GFP_NOWARN ; 
 int __GFP_THISNODE ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __pa (void*) ; 
 struct page* alloc_pages_node (int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* core_imc_pmu ; 
 TYPE_1__* core_imc_refc ; 
 int cpu_to_node (int) ; 
 int /*<<< orphan*/  free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_hard_smp_processor_id (int) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int opal_imc_counters_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * page_address (struct page*) ; 
 int threads_per_core ; 

__attribute__((used)) static int core_imc_mem_init(int cpu, int size)
{
	int nid, rc = 0, core_id = (cpu / threads_per_core);
	struct imc_mem_info *mem_info;
	struct page *page;

	/*
	 * alloc_pages_node() will allocate memory for core in the
	 * local node only.
	 */
	nid = cpu_to_node(cpu);
	mem_info = &core_imc_pmu->mem_info[core_id];
	mem_info->id = core_id;

	/* We need only vbase for core counters */
	page = alloc_pages_node(nid,
				GFP_KERNEL | __GFP_ZERO | __GFP_THISNODE |
				__GFP_NOWARN, get_order(size));
	if (!page)
		return -ENOMEM;
	mem_info->vbase = page_address(page);

	/* Init the mutex */
	core_imc_refc[core_id].id = core_id;
	mutex_init(&core_imc_refc[core_id].lock);

	rc = opal_imc_counters_init(OPAL_IMC_COUNTERS_CORE,
				__pa((void *)mem_info->vbase),
				get_hard_smp_processor_id(cpu));
	if (rc) {
		free_pages((u64)mem_info->vbase, get_order(size));
		mem_info->vbase = NULL;
	}

	return rc;
}