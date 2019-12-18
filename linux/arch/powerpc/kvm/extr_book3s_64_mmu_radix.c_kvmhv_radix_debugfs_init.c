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
struct TYPE_2__ {int /*<<< orphan*/  debugfs_dir; int /*<<< orphan*/  radix_dentry; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_radix_fops ; 

void kvmhv_radix_debugfs_init(struct kvm *kvm)
{
	kvm->arch.radix_dentry = debugfs_create_file("radix", 0400,
						     kvm->arch.debugfs_dir, kvm,
						     &debugfs_radix_fops);
}