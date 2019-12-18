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
typedef  int /*<<< orphan*/  vmci_id ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vmci_handle {int dummy; } ;
struct TYPE_2__ {scalar_t__ payload_size; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct vmci_doorbell_link_msg {int /*<<< orphan*/  notify_idx; struct vmci_handle handle; TYPE_1__ hdr; } ;
struct vmci_datagram {int dummy; } ;
typedef  int /*<<< orphan*/  link_msg ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  VMCI_ANON_SRC_HANDLE ; 
 scalar_t__ VMCI_DG_HEADERSIZE ; 
 int /*<<< orphan*/  VMCI_DOORBELL_LINK ; 
 int VMCI_ERROR_UNAVAILABLE ; 
 int /*<<< orphan*/  VMCI_HANDLE_INVALID (struct vmci_handle) ; 
 int /*<<< orphan*/  VMCI_HYPERVISOR_CONTEXT_ID ; 
 int /*<<< orphan*/  VMCI_MAKE_HANDLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmci_send_datagram (struct vmci_datagram*) ; 

__attribute__((used)) static int
vmci_doorbell_link(struct vmci_handle handle, bool is_doorbell,
    uint32_t notify_idx)
{
	struct vmci_doorbell_link_msg link_msg;
	vmci_id resource_id;

	ASSERT(!VMCI_HANDLE_INVALID(handle));

	if (is_doorbell)
		resource_id = VMCI_DOORBELL_LINK;
	else {
		ASSERT(false);
		return (VMCI_ERROR_UNAVAILABLE);
	}

	link_msg.hdr.dst = VMCI_MAKE_HANDLE(VMCI_HYPERVISOR_CONTEXT_ID,
	    resource_id);
	link_msg.hdr.src = VMCI_ANON_SRC_HANDLE;
	link_msg.hdr.payload_size = sizeof(link_msg) - VMCI_DG_HEADERSIZE;
	link_msg.handle = handle;
	link_msg.notify_idx = notify_idx;

	return (vmci_send_datagram((struct vmci_datagram *)&link_msg));
}