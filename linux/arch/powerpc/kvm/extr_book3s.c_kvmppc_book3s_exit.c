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

/* Variables and functions */
 int /*<<< orphan*/  kvm_exit () ; 
 int /*<<< orphan*/  kvmppc_book3s_exit_pr () ; 
 int /*<<< orphan*/  kvmppc_xive_exit_module () ; 
 int /*<<< orphan*/  kvmppc_xive_native_exit_module () ; 
 scalar_t__ xics_on_xive () ; 

__attribute__((used)) static void kvmppc_book3s_exit(void)
{
#ifdef CONFIG_KVM_XICS
	if (xics_on_xive()) {
		kvmppc_xive_exit_module();
		kvmppc_xive_native_exit_module();
	}
#endif
#ifdef CONFIG_KVM_BOOK3S_32_HANDLER
	kvmppc_book3s_exit_pr();
#endif
	kvm_exit();
}