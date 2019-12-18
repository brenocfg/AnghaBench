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
struct kvm_hv {int /*<<< orphan*/  hv_lock; int /*<<< orphan*/  conn_to_evt; } ;
struct TYPE_2__ {struct kvm_hv hyperv; } ;
struct kvm {int /*<<< orphan*/  srcu; TYPE_1__ arch; } ;
struct eventfd_ctx {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  eventfd_ctx_put (struct eventfd_ctx*) ; 
 struct eventfd_ctx* idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_hv_eventfd_deassign(struct kvm *kvm, u32 conn_id)
{
	struct kvm_hv *hv = &kvm->arch.hyperv;
	struct eventfd_ctx *eventfd;

	mutex_lock(&hv->hv_lock);
	eventfd = idr_remove(&hv->conn_to_evt, conn_id);
	mutex_unlock(&hv->hv_lock);

	if (!eventfd)
		return -ENOENT;

	synchronize_srcu(&kvm->srcu);
	eventfd_ctx_put(eventfd);
	return 0;
}