#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vmci_qpair {int flags; int /*<<< orphan*/  event; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_QPFLAG_LOCAL ; 
 int /*<<< orphan*/  vmci_destroy_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_free_kernel_mem (struct vmci_qpair*,int) ; 
 int vmci_queue_pair_detach (int /*<<< orphan*/ ) ; 

int
vmci_qpair_detach(struct vmci_qpair **qpair)
{
	struct vmci_qpair *old_qpair;
	int result;

	if (!qpair || !(*qpair))
		return (VMCI_ERROR_INVALID_ARGS);

	old_qpair = *qpair;
	result = vmci_queue_pair_detach(old_qpair->handle);

	/*
	 * The guest can fail to detach for a number of reasons, and if it does
	 * so, it will cleanup the entry (if there is one). We need to release
	 * the qpair struct here; there isn't much the caller can do, and we
	 * don't want to leak.
	 */

	if (old_qpair->flags & VMCI_QPFLAG_LOCAL)
		vmci_destroy_event(&old_qpair->event);

	vmci_free_kernel_mem(old_qpair, sizeof(*old_qpair));
	*qpair = NULL;

	return (result);
}