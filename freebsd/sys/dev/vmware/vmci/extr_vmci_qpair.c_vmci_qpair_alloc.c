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
typedef  int /*<<< orphan*/  vmci_privilege_flags ;
typedef  int /*<<< orphan*/  vmci_id ;
typedef  int /*<<< orphan*/ * vmci_event_release_cb ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct vmci_handle {int dummy; } ;
struct vmci_qpair {int flags; struct vmci_handle handle; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  peer; scalar_t__ consume_q_size; int /*<<< orphan*/  consume_q; scalar_t__ produce_q_size; int /*<<< orphan*/  produce_q; } ;

/* Variables and functions */
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_NO_MEM ; 
 int VMCI_ERROR_NO_RESOURCES ; 
 scalar_t__ VMCI_MAX_GUEST_QP_MEMORY ; 
 int /*<<< orphan*/  VMCI_MEMORY_NORMAL ; 
 int VMCI_QPFLAG_NONBLOCK ; 
 int VMCI_SUCCESS ; 
 struct vmci_qpair* vmci_alloc_kernel_mem (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_free_kernel_mem (struct vmci_qpair*,int) ; 
 int vmci_queue_pair_alloc (struct vmci_handle*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
vmci_qpair_alloc(struct vmci_qpair **qpair, struct vmci_handle *handle,
    uint64_t produce_q_size, uint64_t consume_q_size, vmci_id peer,
    uint32_t flags, vmci_privilege_flags priv_flags)
{
	struct vmci_qpair *my_qpair;
	vmci_event_release_cb wakeup_cb;
	void *client_data;
	int retval;

	/*
	 * Restrict the size of a queuepair. Though the device enforces a limit
	 * on the total amount of memory that can be allocated to queuepairs for
	 * a guest, we avoid unnecessarily allocating a lot of memory. Also, we
	 * try to allocate this memory before we make the queuepair allocation
	 * hypercall.
	 *
	 * (Note that this doesn't prevent all cases; a user with only this much
	 * physical memory could still get into trouble.) The error used by the
	 * device is NO_RESOURCES, so use that here too.
	 */

	if (produce_q_size + consume_q_size <
	    MAX(produce_q_size, consume_q_size) ||
	    produce_q_size + consume_q_size > VMCI_MAX_GUEST_QP_MEMORY)
		return (VMCI_ERROR_NO_RESOURCES);

	if (flags & VMCI_QPFLAG_NONBLOCK)
		return (VMCI_ERROR_INVALID_ARGS);

	my_qpair = vmci_alloc_kernel_mem(sizeof(*my_qpair), VMCI_MEMORY_NORMAL);
	if (!my_qpair)
		return (VMCI_ERROR_NO_MEM);

	my_qpair->produce_q_size = produce_q_size;
	my_qpair->consume_q_size = consume_q_size;
	my_qpair->peer = peer;
	my_qpair->flags = flags;
	my_qpair->priv_flags = priv_flags;

	client_data = NULL;
	wakeup_cb = NULL;

	retval = vmci_queue_pair_alloc(handle, &my_qpair->produce_q,
	    my_qpair->produce_q_size, &my_qpair->consume_q,
	    my_qpair->consume_q_size, my_qpair->peer, my_qpair->flags,
	    my_qpair->priv_flags);

	if (retval < VMCI_SUCCESS) {
		vmci_free_kernel_mem(my_qpair, sizeof(*my_qpair));
		return (retval);
	}

	*qpair = my_qpair;
	my_qpair->handle = *handle;

	return (retval);
}