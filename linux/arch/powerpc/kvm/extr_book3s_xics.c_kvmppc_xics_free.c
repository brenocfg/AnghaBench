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
struct kvmppc_xics {int max_icsid; struct kvmppc_xics** ics; int /*<<< orphan*/  dentry; struct kvm* kvm; struct kvmppc_xics* private; } ;
struct kvm_device {int max_icsid; struct kvm_device** ics; int /*<<< orphan*/  dentry; struct kvm* kvm; struct kvm_device* private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * xics; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvmppc_xics*) ; 

__attribute__((used)) static void kvmppc_xics_free(struct kvm_device *dev)
{
	struct kvmppc_xics *xics = dev->private;
	int i;
	struct kvm *kvm = xics->kvm;

	debugfs_remove(xics->dentry);

	if (kvm)
		kvm->arch.xics = NULL;

	for (i = 0; i <= xics->max_icsid; i++)
		kfree(xics->ics[i]);
	kfree(xics);
	kfree(dev);
}