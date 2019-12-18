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
struct kvm_vcpu {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  READING_SHADOW_PAGE_TABLES ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  kvm_trap_emul_check_requests (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  smp_store_mb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvm_trap_emul_gva_lockless_begin(struct kvm_vcpu *vcpu)
{
	/* We re-enable IRQs in kvm_trap_emul_gva_lockless_end() */
	WARN_ON_ONCE(irqs_disabled());

	/*
	 * The caller is about to access the GVA space, so we set the mode to
	 * force TLB flush requests to send an IPI, and also disable IRQs to
	 * delay IPI handling until kvm_trap_emul_gva_lockless_end().
	 */
	local_irq_disable();

	/*
	 * Make sure the read of VCPU requests is not reordered ahead of the
	 * write to vcpu->mode, or we could miss a TLB flush request while
	 * the requester sees the VCPU as outside of guest mode and not needing
	 * an IPI.
	 */
	smp_store_mb(vcpu->mode, READING_SHADOW_PAGE_TABLES);

	/*
	 * If a TLB flush has been requested (potentially while
	 * OUTSIDE_GUEST_MODE and assumed immediately effective), perform it
	 * before accessing the GVA space, and be sure to reload the ASID if
	 * necessary as it'll be immediately used.
	 *
	 * TLB flush requests after this check will trigger an IPI due to the
	 * mode change above, which will be delayed due to IRQs disabled.
	 */
	kvm_trap_emul_check_requests(vcpu, smp_processor_id(), true);
}