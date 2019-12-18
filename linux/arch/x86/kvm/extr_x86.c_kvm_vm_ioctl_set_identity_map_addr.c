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
typedef  int /*<<< orphan*/  u64 ;
struct kvm {int dummy; } ;
struct TYPE_2__ {int (* set_identity_map_addr ) (struct kvm*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (struct kvm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_vm_ioctl_set_identity_map_addr(struct kvm *kvm,
					      u64 ident_addr)
{
	return kvm_x86_ops->set_identity_map_addr(kvm, ident_addr);
}