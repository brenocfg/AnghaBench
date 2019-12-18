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
struct kvm_vcpu {int /*<<< orphan*/  debugfs_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_has_tsc_control ; 
 scalar_t__ lapic_in_kernel (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_timer_advance_ns_fops ; 
 int /*<<< orphan*/  vcpu_tsc_offset_fops ; 
 int /*<<< orphan*/  vcpu_tsc_scaling_fops ; 
 int /*<<< orphan*/  vcpu_tsc_scaling_frac_fops ; 

void kvm_arch_create_vcpu_debugfs(struct kvm_vcpu *vcpu)
{
	debugfs_create_file("tsc-offset", 0444, vcpu->debugfs_dentry, vcpu,
			    &vcpu_tsc_offset_fops);

	if (lapic_in_kernel(vcpu))
		debugfs_create_file("lapic_timer_advance_ns", 0444,
				    vcpu->debugfs_dentry, vcpu,
				    &vcpu_timer_advance_ns_fops);

	if (kvm_has_tsc_control) {
		debugfs_create_file("tsc-scaling-ratio", 0444,
				    vcpu->debugfs_dentry, vcpu,
				    &vcpu_tsc_scaling_fops);
		debugfs_create_file("tsc-scaling-ratio-frac-bits", 0444,
				    vcpu->debugfs_dentry, vcpu,
				    &vcpu_tsc_scaling_frac_fops);
	}
}