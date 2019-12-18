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
struct kvmppc_xive {scalar_t__ q_order; scalar_t__ vp_base; int /*<<< orphan*/  single_escalation; scalar_t__ q_page_order; int /*<<< orphan*/  lock; struct kvm* kvm; struct kvm_device* dev; } ;
struct kvm_device {struct kvmppc_xive* private; struct kvm* kvm; } ;
struct TYPE_2__ {struct kvmppc_xive* xive; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KVM_MAX_VCPUS ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ XIVE_INVALID_VP ; 
 struct kvmppc_xive* kvmppc_xive_get_device (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_devel (char*,...) ; 
 scalar_t__ xive_native_alloc_vp_block (int /*<<< orphan*/ ) ; 
 scalar_t__ xive_native_default_eq_shift () ; 
 int /*<<< orphan*/  xive_native_has_single_escalation () ; 

__attribute__((used)) static int kvmppc_xive_create(struct kvm_device *dev, u32 type)
{
	struct kvmppc_xive *xive;
	struct kvm *kvm = dev->kvm;
	int ret = 0;

	pr_devel("Creating xive for partition\n");

	xive = kvmppc_xive_get_device(kvm, type);
	if (!xive)
		return -ENOMEM;

	dev->private = xive;
	xive->dev = dev;
	xive->kvm = kvm;
	mutex_init(&xive->lock);

	/* Already there ? */
	if (kvm->arch.xive)
		ret = -EEXIST;
	else
		kvm->arch.xive = xive;

	/* We use the default queue size set by the host */
	xive->q_order = xive_native_default_eq_shift();
	if (xive->q_order < PAGE_SHIFT)
		xive->q_page_order = 0;
	else
		xive->q_page_order = xive->q_order - PAGE_SHIFT;

	/* Allocate a bunch of VPs */
	xive->vp_base = xive_native_alloc_vp_block(KVM_MAX_VCPUS);
	pr_devel("VP_Base=%x\n", xive->vp_base);

	if (xive->vp_base == XIVE_INVALID_VP)
		ret = -ENOMEM;

	xive->single_escalation = xive_native_has_single_escalation();

	if (ret)
		return ret;

	return 0;
}