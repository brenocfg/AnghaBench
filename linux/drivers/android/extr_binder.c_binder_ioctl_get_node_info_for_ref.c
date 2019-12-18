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
struct binder_proc {int /*<<< orphan*/  pid; struct binder_context* context; } ;
struct binder_node_info_for_ref {int /*<<< orphan*/  weak_count; scalar_t__ strong_count; scalar_t__ reserved3; scalar_t__ reserved2; scalar_t__ reserved1; int /*<<< orphan*/  handle; } ;
struct binder_node {int /*<<< orphan*/  local_weak_refs; scalar_t__ internal_strong_refs; scalar_t__ local_strong_refs; } ;
struct binder_context {int /*<<< orphan*/  context_mgr_node_lock; TYPE_1__* binder_context_mgr_node; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {struct binder_proc* proc; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 struct binder_node* binder_get_node_from_ref (struct binder_proc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_put_node (struct binder_node*) ; 
 int /*<<< orphan*/  binder_user_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int binder_ioctl_get_node_info_for_ref(struct binder_proc *proc,
		struct binder_node_info_for_ref *info)
{
	struct binder_node *node;
	struct binder_context *context = proc->context;
	__u32 handle = info->handle;

	if (info->strong_count || info->weak_count || info->reserved1 ||
	    info->reserved2 || info->reserved3) {
		binder_user_error("%d BINDER_GET_NODE_INFO_FOR_REF: only handle may be non-zero.",
				  proc->pid);
		return -EINVAL;
	}

	/* This ioctl may only be used by the context manager */
	mutex_lock(&context->context_mgr_node_lock);
	if (!context->binder_context_mgr_node ||
		context->binder_context_mgr_node->proc != proc) {
		mutex_unlock(&context->context_mgr_node_lock);
		return -EPERM;
	}
	mutex_unlock(&context->context_mgr_node_lock);

	node = binder_get_node_from_ref(proc, handle, true, NULL);
	if (!node)
		return -EINVAL;

	info->strong_count = node->local_strong_refs +
		node->internal_strong_refs;
	info->weak_count = node->local_weak_refs;

	binder_put_node(node);

	return 0;
}