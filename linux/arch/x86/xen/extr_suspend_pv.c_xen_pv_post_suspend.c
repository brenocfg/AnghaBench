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
struct TYPE_4__ {void* mfn; } ;
struct TYPE_5__ {TYPE_1__ domU; } ;
struct TYPE_6__ {TYPE_2__ console; void* store_mfn; int /*<<< orphan*/  shared_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIX_PARAVIRT_BOOTMAP ; 
 void* HYPERVISOR_shared_info ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fix_to_virt (int /*<<< orphan*/ ) ; 
 void* pfn_to_mfn (void*) ; 
 int /*<<< orphan*/  set_fixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_build_mfn_list_list () ; 
 int /*<<< orphan*/ * xen_cpu_initialized_map ; 
 int /*<<< orphan*/  xen_mm_unpin_all () ; 
 int /*<<< orphan*/  xen_setup_mfn_list_list () ; 
 TYPE_3__* xen_start_info ; 
 int /*<<< orphan*/  xen_vcpu_restore () ; 

void xen_pv_post_suspend(int suspend_cancelled)
{
	xen_build_mfn_list_list();
	set_fixmap(FIX_PARAVIRT_BOOTMAP, xen_start_info->shared_info);
	HYPERVISOR_shared_info = (void *)fix_to_virt(FIX_PARAVIRT_BOOTMAP);
	xen_setup_mfn_list_list();

	if (suspend_cancelled) {
		xen_start_info->store_mfn =
			pfn_to_mfn(xen_start_info->store_mfn);
		xen_start_info->console.domU.mfn =
			pfn_to_mfn(xen_start_info->console.domU.mfn);
	} else {
#ifdef CONFIG_SMP
		BUG_ON(xen_cpu_initialized_map == NULL);
		cpumask_copy(xen_cpu_initialized_map, cpu_online_mask);
#endif
		xen_vcpu_restore();
	}

	xen_mm_unpin_all();
}