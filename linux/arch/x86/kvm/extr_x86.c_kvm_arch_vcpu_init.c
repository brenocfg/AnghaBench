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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_5__ {int mcg_cap; int pending_external_vector; int preempted_in_kernel; scalar_t__ pio_data; int /*<<< orphan*/  mce_banks; int /*<<< orphan*/  pat; int /*<<< orphan*/  maxphyaddr; scalar_t__ guest_xstate_size; int /*<<< orphan*/  wbinvd_dirty_mask; int /*<<< orphan*/  apicv_active; int /*<<< orphan*/  mp_state; TYPE_1__ emulate_ctxt; } ;
struct kvm_vcpu {TYPE_2__ arch; int /*<<< orphan*/  kvm; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_enable_apicv ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int KVM_MAX_MCE_BANKS ; 
 int /*<<< orphan*/  KVM_MP_STATE_RUNNABLE ; 
 int /*<<< orphan*/  KVM_MP_STATE_UNINITIALIZED ; 
 int /*<<< orphan*/  MSR_IA32_CR_PAT_DEFAULT ; 
 scalar_t__ XSAVE_HDR_OFFSET ; 
 scalar_t__ XSAVE_HDR_SIZE ; 
 int __GFP_ZERO ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  cpuid_query_maxphyaddr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  emulate_ops ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  fx_init (struct kvm_vcpu*) ; 
 scalar_t__ irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_async_pf_hash_reset (struct kvm_vcpu*) ; 
 int kvm_create_lapic (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_free_lapic (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_hv_vcpu_init (struct kvm_vcpu*) ; 
 int kvm_mmu_create (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_destroy (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_no_apic_vcpu ; 
 int /*<<< orphan*/  kvm_pmu_init (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_set_tsc_khz (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_vcpu_is_reset_bsp (struct kvm_vcpu*) ; 
 TYPE_3__* kvm_x86_ops ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_timer_advance_ns ; 
 int /*<<< orphan*/  max_tsc_khz ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  static_key_slow_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int kvm_arch_vcpu_init(struct kvm_vcpu *vcpu)
{
	struct page *page;
	int r;

	vcpu->arch.emulate_ctxt.ops = &emulate_ops;
	if (!irqchip_in_kernel(vcpu->kvm) || kvm_vcpu_is_reset_bsp(vcpu))
		vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;
	else
		vcpu->arch.mp_state = KVM_MP_STATE_UNINITIALIZED;

	page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (!page) {
		r = -ENOMEM;
		goto fail;
	}
	vcpu->arch.pio_data = page_address(page);

	kvm_set_tsc_khz(vcpu, max_tsc_khz);

	r = kvm_mmu_create(vcpu);
	if (r < 0)
		goto fail_free_pio_data;

	if (irqchip_in_kernel(vcpu->kvm)) {
		vcpu->arch.apicv_active = kvm_x86_ops->get_enable_apicv(vcpu);
		r = kvm_create_lapic(vcpu, lapic_timer_advance_ns);
		if (r < 0)
			goto fail_mmu_destroy;
	} else
		static_key_slow_inc(&kvm_no_apic_vcpu);

	vcpu->arch.mce_banks = kzalloc(KVM_MAX_MCE_BANKS * sizeof(u64) * 4,
				       GFP_KERNEL_ACCOUNT);
	if (!vcpu->arch.mce_banks) {
		r = -ENOMEM;
		goto fail_free_lapic;
	}
	vcpu->arch.mcg_cap = KVM_MAX_MCE_BANKS;

	if (!zalloc_cpumask_var(&vcpu->arch.wbinvd_dirty_mask,
				GFP_KERNEL_ACCOUNT)) {
		r = -ENOMEM;
		goto fail_free_mce_banks;
	}

	fx_init(vcpu);

	vcpu->arch.guest_xstate_size = XSAVE_HDR_SIZE + XSAVE_HDR_OFFSET;

	vcpu->arch.maxphyaddr = cpuid_query_maxphyaddr(vcpu);

	vcpu->arch.pat = MSR_IA32_CR_PAT_DEFAULT;

	kvm_async_pf_hash_reset(vcpu);
	kvm_pmu_init(vcpu);

	vcpu->arch.pending_external_vector = -1;
	vcpu->arch.preempted_in_kernel = false;

	kvm_hv_vcpu_init(vcpu);

	return 0;

fail_free_mce_banks:
	kfree(vcpu->arch.mce_banks);
fail_free_lapic:
	kvm_free_lapic(vcpu);
fail_mmu_destroy:
	kvm_mmu_destroy(vcpu);
fail_free_pio_data:
	free_page((unsigned long)vcpu->arch.pio_data);
fail:
	return r;
}