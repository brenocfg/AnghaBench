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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_DEV_TYPE_XICS ; 
 int /*<<< orphan*/  KVM_DEV_TYPE_XIVE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int kvm_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_register_device_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_xics_ops ; 
 int /*<<< orphan*/  kvm_xive_native_ops ; 
 int /*<<< orphan*/  kvm_xive_ops ; 
 int kvmppc_book3s_init_pr () ; 
 int /*<<< orphan*/  kvmppc_xive_init_module () ; 
 int /*<<< orphan*/  kvmppc_xive_native_init_module () ; 
 scalar_t__ kvmppc_xive_native_supported () ; 
 scalar_t__ xics_on_xive () ; 

__attribute__((used)) static int kvmppc_book3s_init(void)
{
	int r;

	r = kvm_init(NULL, sizeof(struct kvm_vcpu), 0, THIS_MODULE);
	if (r)
		return r;
#ifdef CONFIG_KVM_BOOK3S_32_HANDLER
	r = kvmppc_book3s_init_pr();
#endif

#ifdef CONFIG_KVM_XICS
#ifdef CONFIG_KVM_XIVE
	if (xics_on_xive()) {
		kvmppc_xive_init_module();
		kvm_register_device_ops(&kvm_xive_ops, KVM_DEV_TYPE_XICS);
		if (kvmppc_xive_native_supported()) {
			kvmppc_xive_native_init_module();
			kvm_register_device_ops(&kvm_xive_native_ops,
						KVM_DEV_TYPE_XIVE);
		}
	} else
#endif
		kvm_register_device_ops(&kvm_xics_ops, KVM_DEV_TYPE_XICS);
#endif
	return r;
}