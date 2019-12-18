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
typedef  int /*<<< orphan*/  u32 ;
struct x86_exception {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;
struct TYPE_2__ {int (* get_cpl ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PFERR_USER_MASK ; 
 int kvm_read_guest_virt_helper (int /*<<< orphan*/ ,void*,unsigned int,struct kvm_vcpu*,int /*<<< orphan*/ ,struct x86_exception*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  memset (struct x86_exception*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct kvm_vcpu*) ; 

int kvm_read_guest_virt(struct kvm_vcpu *vcpu,
			       gva_t addr, void *val, unsigned int bytes,
			       struct x86_exception *exception)
{
	u32 access = (kvm_x86_ops->get_cpl(vcpu) == 3) ? PFERR_USER_MASK : 0;

	/*
	 * FIXME: this should call handle_emulation_failure if X86EMUL_IO_NEEDED
	 * is returned, but our callers are not ready for that and they blindly
	 * call kvm_inject_page_fault.  Ensure that they at least do not leak
	 * uninitialized kernel stack memory into cr2 and error code.
	 */
	memset(exception, 0, sizeof(*exception));
	return kvm_read_guest_virt_helper(addr, val, bytes, vcpu, access,
					  exception);
}