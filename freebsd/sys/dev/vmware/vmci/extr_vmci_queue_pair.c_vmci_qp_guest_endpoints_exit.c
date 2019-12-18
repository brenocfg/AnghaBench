#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; scalar_t__ ref_count; int /*<<< orphan*/  handle; } ;
struct qp_guest_endpoint {TYPE_2__ qp; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  hibernate; } ;

/* Variables and functions */
 int VMCI_QPFLAG_LOCAL ; 
 int /*<<< orphan*/  atomic_store_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qp_guest_endpoint_destroy (struct qp_guest_endpoint*) ; 
 TYPE_1__ qp_guest_endpoints ; 
 int /*<<< orphan*/  queue_pair_list_destroy (TYPE_1__*) ; 
 scalar_t__ queue_pair_list_get_head (TYPE_1__*) ; 
 int /*<<< orphan*/  queue_pair_list_remove_entry (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vmci_mutex_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_mutex_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_queue_pair_detach_hypercall (int /*<<< orphan*/ ) ; 

void
vmci_qp_guest_endpoints_exit(void)
{
	struct qp_guest_endpoint *entry;

	vmci_mutex_acquire(&qp_guest_endpoints.mutex);

	while ((entry =
	    (struct qp_guest_endpoint *)queue_pair_list_get_head(
	    &qp_guest_endpoints)) != NULL) {
		/*
		 * Don't make a hypercall for local QueuePairs.
		 */
		if (!(entry->qp.flags & VMCI_QPFLAG_LOCAL))
			vmci_queue_pair_detach_hypercall(entry->qp.handle);
		/*
		 * We cannot fail the exit, so let's reset ref_count.
		 */
		entry->qp.ref_count = 0;
		queue_pair_list_remove_entry(&qp_guest_endpoints, &entry->qp);
		qp_guest_endpoint_destroy(entry);
	}

	atomic_store_int(&qp_guest_endpoints.hibernate, 0);
	vmci_mutex_release(&qp_guest_endpoints.mutex);
	queue_pair_list_destroy(&qp_guest_endpoints);
}