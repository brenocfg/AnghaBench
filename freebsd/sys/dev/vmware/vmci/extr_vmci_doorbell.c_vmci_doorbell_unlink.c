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
typedef  int /*<<< orphan*/  unlink_msg ;
struct vmci_handle {int dummy; } ;
struct TYPE_2__ {scalar_t__ payload_size; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct vmci_doorbell_unlink_msg {struct vmci_handle handle; TYPE_1__ hdr; } ;
struct vmci_datagram {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  VMCI_ANON_SRC_HANDLE ; 
 scalar_t__ VMCI_DG_HEADERSIZE ; 
 int /*<<< orphan*/  VMCI_DOORBELL_UNLINK ; 
 int VMCI_ERROR_UNAVAILABLE ; 
 int /*<<< orphan*/  VMCI_HANDLE_INVALID (struct vmci_handle) ; 
 int /*<<< orphan*/  VMCI_HYPERVISOR_CONTEXT_ID ; 
 int /*<<< orphan*/  VMCI_MAKE_HANDLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmci_send_datagram (struct vmci_datagram*) ; 

__attribute__((used)) static int
vmci_doorbell_unlink(struct vmci_handle handle, bool is_doorbell)
{
	struct vmci_doorbell_unlink_msg unlink_msg;
	vmci_id resource_id;

	ASSERT(!VMCI_HANDLE_INVALID(handle));

	if (is_doorbell)
		resource_id = VMCI_DOORBELL_UNLINK;
	else {
		ASSERT(false);
		return (VMCI_ERROR_UNAVAILABLE);
	}

	unlink_msg.hdr.dst = VMCI_MAKE_HANDLE(VMCI_HYPERVISOR_CONTEXT_ID,
	    resource_id);
	unlink_msg.hdr.src = VMCI_ANON_SRC_HANDLE;
	unlink_msg.hdr.payload_size = sizeof(unlink_msg) - VMCI_DG_HEADERSIZE;
	unlink_msg.handle = handle;

	return (vmci_send_datagram((struct vmci_datagram *)&unlink_msg));
}