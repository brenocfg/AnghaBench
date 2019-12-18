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
struct kvmppc_xics {int /*<<< orphan*/  real_mode_dbg; int /*<<< orphan*/  real_mode; struct kvm* kvm; struct kvm_device* dev; } ;
struct kvm_device {struct kvmppc_xics* private; struct kvm* kvm; } ;
struct TYPE_2__ {struct kvmppc_xics* xics; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_206 ; 
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int /*<<< orphan*/  DEBUG_REALMODE ; 
 int EEXIST ; 
 int /*<<< orphan*/  ENABLE_REALMODE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvmppc_xics*) ; 
 struct kvmppc_xics* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvmppc_xics_create(struct kvm_device *dev, u32 type)
{
	struct kvmppc_xics *xics;
	struct kvm *kvm = dev->kvm;
	int ret = 0;

	xics = kzalloc(sizeof(*xics), GFP_KERNEL);
	if (!xics)
		return -ENOMEM;

	dev->private = xics;
	xics->dev = dev;
	xics->kvm = kvm;

	/* Already there ? */
	if (kvm->arch.xics)
		ret = -EEXIST;
	else
		kvm->arch.xics = xics;

	if (ret) {
		kfree(xics);
		return ret;
	}

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBLE
	if (cpu_has_feature(CPU_FTR_ARCH_206) &&
	    cpu_has_feature(CPU_FTR_HVMODE)) {
		/* Enable real mode support */
		xics->real_mode = ENABLE_REALMODE;
		xics->real_mode_dbg = DEBUG_REALMODE;
	}
#endif /* CONFIG_KVM_BOOK3S_HV_POSSIBLE */

	return 0;
}