#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct kvmppc_xive {int dummy; } ;
struct TYPE_3__ {struct kvmppc_xive* xics_on_xive; struct kvmppc_xive* native; } ;
struct TYPE_4__ {TYPE_1__ xive_devices; } ;
struct kvm {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ KVM_DEV_TYPE_XIVE ; 
 struct kvmppc_xive* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct kvmppc_xive*,int /*<<< orphan*/ ,int) ; 

struct kvmppc_xive *kvmppc_xive_get_device(struct kvm *kvm, u32 type)
{
	struct kvmppc_xive **kvm_xive_device = type == KVM_DEV_TYPE_XIVE ?
		&kvm->arch.xive_devices.native :
		&kvm->arch.xive_devices.xics_on_xive;
	struct kvmppc_xive *xive = *kvm_xive_device;

	if (!xive) {
		xive = kzalloc(sizeof(*xive), GFP_KERNEL);
		*kvm_xive_device = xive;
	} else {
		memset(xive, 0, sizeof(*xive));
	}

	return xive;
}