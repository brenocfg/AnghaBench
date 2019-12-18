#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  owner; } ;
struct TYPE_5__ {int /*<<< orphan*/  xics_phys; } ;
struct TYPE_6__ {TYPE_1__ kvm_hstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int ENODEV ; 
 unsigned int PVR_POWER9 ; 
 int /*<<< orphan*/  SPRN_PVR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_default_hcalls () ; 
 int /*<<< orphan*/  init_vcore_lists () ; 
 int kvm_init_subcore_bitmap () ; 
 TYPE_3__ kvm_ops_hv ; 
 int kvmhv_nested_init () ; 
 int /*<<< orphan*/  kvmhv_on_pseries () ; 
 int kvmppc_core_check_processor_compat_hv () ; 
 TYPE_3__* kvmppc_hv_ops ; 
 int kvmppc_mmu_hv_init () ; 
 int kvmppc_radix_init () ; 
 scalar_t__ kvmppc_radix_possible () ; 
 TYPE_2__* local_paca ; 
 unsigned int mfspr (int /*<<< orphan*/ ) ; 
 int no_mixing_hpt_and_radix ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  tlbie_capable ; 
 int /*<<< orphan*/  xics_on_xive () ; 

__attribute__((used)) static int kvmppc_book3s_init_hv(void)
{
	int r;

	if (!tlbie_capable) {
		pr_err("KVM-HV: Host does not support TLBIE\n");
		return -ENODEV;
	}

	/*
	 * FIXME!! Do we need to check on all cpus ?
	 */
	r = kvmppc_core_check_processor_compat_hv();
	if (r < 0)
		return -ENODEV;

	r = kvmhv_nested_init();
	if (r)
		return r;

	r = kvm_init_subcore_bitmap();
	if (r)
		return r;

	/*
	 * We need a way of accessing the XICS interrupt controller,
	 * either directly, via paca_ptrs[cpu]->kvm_hstate.xics_phys, or
	 * indirectly, via OPAL.
	 */
#ifdef CONFIG_SMP
	if (!xics_on_xive() && !kvmhv_on_pseries() &&
	    !local_paca->kvm_hstate.xics_phys) {
		struct device_node *np;

		np = of_find_compatible_node(NULL, NULL, "ibm,opal-intc");
		if (!np) {
			pr_err("KVM-HV: Cannot determine method for accessing XICS\n");
			return -ENODEV;
		}
		/* presence of intc confirmed - node can be dropped again */
		of_node_put(np);
	}
#endif

	kvm_ops_hv.owner = THIS_MODULE;
	kvmppc_hv_ops = &kvm_ops_hv;

	init_default_hcalls();

	init_vcore_lists();

	r = kvmppc_mmu_hv_init();
	if (r)
		return r;

	if (kvmppc_radix_possible())
		r = kvmppc_radix_init();

	/*
	 * POWER9 chips before version 2.02 can't have some threads in
	 * HPT mode and some in radix mode on the same core.
	 */
	if (cpu_has_feature(CPU_FTR_ARCH_300)) {
		unsigned int pvr = mfspr(SPRN_PVR);
		if ((pvr >> 16) == PVR_POWER9 &&
		    (((pvr & 0xe000) == 0 && (pvr & 0xfff) < 0x202) ||
		     ((pvr & 0xe000) == 0x2000 && (pvr & 0xfff) < 0x101)))
			no_mixing_hpt_and_radix = true;
	}

	return r;
}