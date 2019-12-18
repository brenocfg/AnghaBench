#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vmci_handle {int dummy; } ;
struct TYPE_6__ {int ref_count; int flags; } ;
struct qp_guest_endpoint {TYPE_2__ qp; scalar_t__ hibernate_failure; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int VMCI_ERROR_NOT_FOUND ; 
 int /*<<< orphan*/  VMCI_HANDLE_INVALID (struct vmci_handle) ; 
 int VMCI_QPFLAG_LOCAL ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  qp_guest_endpoint_destroy (struct qp_guest_endpoint*) ; 
 TYPE_1__ qp_guest_endpoints ; 
 scalar_t__ queue_pair_list_find_entry (TYPE_1__*,struct vmci_handle) ; 
 int /*<<< orphan*/  queue_pair_list_remove_entry (TYPE_1__*,TYPE_2__*) ; 
 int queue_pair_notify_peer_local (int,struct vmci_handle) ; 
 int /*<<< orphan*/  vmci_mutex_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_mutex_release (int /*<<< orphan*/ *) ; 
 int vmci_queue_pair_detach_hypercall (struct vmci_handle) ; 

__attribute__((used)) static int
vmci_queue_pair_detach_guest_work(struct vmci_handle handle)
{
	struct qp_guest_endpoint *entry;
	int result;
	uint32_t ref_count;

	ASSERT(!VMCI_HANDLE_INVALID(handle));

	vmci_mutex_acquire(&qp_guest_endpoints.mutex);

	entry = (struct qp_guest_endpoint *)queue_pair_list_find_entry(
	    &qp_guest_endpoints, handle);
	if (!entry) {
		vmci_mutex_release(&qp_guest_endpoints.mutex);
		return (VMCI_ERROR_NOT_FOUND);
	}

	ASSERT(entry->qp.ref_count >= 1);

	if (entry->qp.flags & VMCI_QPFLAG_LOCAL) {
		result = VMCI_SUCCESS;

		if (entry->qp.ref_count > 1) {
			result = queue_pair_notify_peer_local(false, handle);

			/*
			 * We can fail to notify a local queuepair because we
			 * can't allocate. We still want to release the entry
			 * if that happens, so don't bail out yet.
			 */
		}
	} else {
		result = vmci_queue_pair_detach_hypercall(handle);
		if (entry->hibernate_failure) {
			if (result == VMCI_ERROR_NOT_FOUND) {

				/*
				 * If a queue pair detach failed when entering
				 * hibernation, the guest driver and the device
				 * may disagree on its existence when coming
				 * out of hibernation. The guest driver will
				 * regard it as a non-local queue pair, but
				 * the device state is gone, since the device
				 * has been powered off. In this case, we
				 * treat the queue pair as a local queue pair
				 * with no peer.
				 */

				ASSERT(entry->qp.ref_count == 1);
				result = VMCI_SUCCESS;
			}
		}
		if (result < VMCI_SUCCESS) {

			/*
			 * We failed to notify a non-local queuepair. That other
			 * queuepair might still be accessing the shared
			 * memory, so don't release the entry yet. It will get
			 * cleaned up by vmci_queue_pair_Exit() if necessary
			 * (assuming we are going away, otherwise why did this
			 * fail?).
			 */

			vmci_mutex_release(&qp_guest_endpoints.mutex);
			return (result);
		}
	}

	/*
	 * If we get here then we either failed to notify a local queuepair, or
	 * we succeeded in all cases.  Release the entry if required.
	 */

	entry->qp.ref_count--;
	if (entry->qp.ref_count == 0)
		queue_pair_list_remove_entry(&qp_guest_endpoints, &entry->qp);

	/* If we didn't remove the entry, this could change once we unlock. */
	ref_count = entry ? entry->qp.ref_count :
	    0xffffffff; /*
			 * Value does not matter, silence the
			 * compiler.
			 */

	vmci_mutex_release(&qp_guest_endpoints.mutex);

	if (ref_count == 0)
		qp_guest_endpoint_destroy(entry);
	return (result);
}