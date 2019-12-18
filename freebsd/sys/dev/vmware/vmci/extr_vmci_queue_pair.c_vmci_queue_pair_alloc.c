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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct vmci_queue {int dummy; } ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_QP_ALL_FLAGS ; 
 int vmci_queue_pair_alloc_guest_work (struct vmci_handle*,struct vmci_queue**,int /*<<< orphan*/ ,struct vmci_queue**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
vmci_queue_pair_alloc(struct vmci_handle *handle, struct vmci_queue **produce_q,
    uint64_t produce_size, struct vmci_queue **consume_q, uint64_t consume_size,
    vmci_id peer, uint32_t flags, vmci_privilege_flags priv_flags)
{

	if (!handle || !produce_q || !consume_q ||
	    (!produce_size && !consume_size) || (flags & ~VMCI_QP_ALL_FLAGS))
		return (VMCI_ERROR_INVALID_ARGS);

	return (vmci_queue_pair_alloc_guest_work(handle, produce_q,
	    produce_size, consume_q, consume_size, peer, flags, priv_flags));
}