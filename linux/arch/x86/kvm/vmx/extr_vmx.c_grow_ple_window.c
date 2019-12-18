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
struct vcpu_vmx {unsigned int ple_window; int ple_window_dirty; } ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 unsigned int __grow_ple_window (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ple_window ; 
 int /*<<< orphan*/  ple_window_grow ; 
 int /*<<< orphan*/  ple_window_max ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_ple_window_update (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void grow_ple_window(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	unsigned int old = vmx->ple_window;

	vmx->ple_window = __grow_ple_window(old, ple_window,
					    ple_window_grow,
					    ple_window_max);

	if (vmx->ple_window != old) {
		vmx->ple_window_dirty = true;
		trace_kvm_ple_window_update(vcpu->vcpu_id,
					    vmx->ple_window, old);
	}
}