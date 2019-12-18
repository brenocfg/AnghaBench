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
struct x86_exception {int dummy; } ;
struct TYPE_2__ {int l1tf_flush_l1d; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  gva_t ;

/* Variables and functions */
 int /*<<< orphan*/  PFERR_WRITE_MASK ; 
 int kvm_write_guest_virt_helper (int /*<<< orphan*/ ,void*,unsigned int,struct kvm_vcpu*,int /*<<< orphan*/ ,struct x86_exception*) ; 
 int /*<<< orphan*/  memset (struct x86_exception*,int /*<<< orphan*/ ,int) ; 

int kvm_write_guest_virt_system(struct kvm_vcpu *vcpu, gva_t addr, void *val,
				unsigned int bytes, struct x86_exception *exception)
{
	/* kvm_write_guest_virt_system can pull in tons of pages. */
	vcpu->arch.l1tf_flush_l1d = true;

	/*
	 * FIXME: this should call handle_emulation_failure if X86EMUL_IO_NEEDED
	 * is returned, but our callers are not ready for that and they blindly
	 * call kvm_inject_page_fault.  Ensure that they at least do not leak
	 * uninitialized kernel stack memory into cr2 and error code.
	 */
	memset(exception, 0, sizeof(*exception));
	return kvm_write_guest_virt_helper(addr, val, bytes, vcpu,
					   PFERR_WRITE_MASK, exception);
}