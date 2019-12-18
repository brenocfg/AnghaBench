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
struct vmcs_host_state {int dummy; } ;
struct vmcs_controls_shadow {int dummy; } ;
struct loaded_vmcs {int hv_timer_soft_disabled; unsigned long* msr_bitmap; unsigned long host_state; unsigned long controls_shadow; scalar_t__ vmcs; int /*<<< orphan*/ * shadow_vmcs; } ;
struct TYPE_3__ {int msr_bitmap; } ;
struct hv_enlightened_vmcs {TYPE_1__ hv_enlightenments_control; } ;
struct TYPE_4__ {int nested_features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HYPERV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int HV_X64_NESTED_MSR_BITMAP ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 scalar_t__ alloc_vmcs (int) ; 
 scalar_t__ cpu_has_vmx_msr_bitmap () ; 
 int /*<<< orphan*/  enable_evmcs ; 
 int /*<<< orphan*/  free_loaded_vmcs (struct loaded_vmcs*) ; 
 int /*<<< orphan*/  loaded_vmcs_init (struct loaded_vmcs*) ; 
 int /*<<< orphan*/  memset (unsigned long*,int,int) ; 
 TYPE_2__ ms_hyperv ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 

int alloc_loaded_vmcs(struct loaded_vmcs *loaded_vmcs)
{
	loaded_vmcs->vmcs = alloc_vmcs(false);
	if (!loaded_vmcs->vmcs)
		return -ENOMEM;

	loaded_vmcs->shadow_vmcs = NULL;
	loaded_vmcs->hv_timer_soft_disabled = false;
	loaded_vmcs_init(loaded_vmcs);

	if (cpu_has_vmx_msr_bitmap()) {
		loaded_vmcs->msr_bitmap = (unsigned long *)
				__get_free_page(GFP_KERNEL_ACCOUNT);
		if (!loaded_vmcs->msr_bitmap)
			goto out_vmcs;
		memset(loaded_vmcs->msr_bitmap, 0xff, PAGE_SIZE);

		if (IS_ENABLED(CONFIG_HYPERV) &&
		    static_branch_unlikely(&enable_evmcs) &&
		    (ms_hyperv.nested_features & HV_X64_NESTED_MSR_BITMAP)) {
			struct hv_enlightened_vmcs *evmcs =
				(struct hv_enlightened_vmcs *)loaded_vmcs->vmcs;

			evmcs->hv_enlightenments_control.msr_bitmap = 1;
		}
	}

	memset(&loaded_vmcs->host_state, 0, sizeof(struct vmcs_host_state));
	memset(&loaded_vmcs->controls_shadow, 0,
		sizeof(struct vmcs_controls_shadow));

	return 0;

out_vmcs:
	free_loaded_vmcs(loaded_vmcs);
	return -ENOMEM;
}