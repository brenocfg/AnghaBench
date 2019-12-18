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
struct vmci_handle {int dummy; } ;
struct TYPE_2__ {int payload_size; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct vmci_queue_pair_detach_msg {struct vmci_handle handle; TYPE_1__ hdr; } ;
struct vmci_datagram {int dummy; } ;
typedef  int /*<<< orphan*/  handle ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_ANON_SRC_HANDLE ; 
 int /*<<< orphan*/  VMCI_HYPERVISOR_CONTEXT_ID ; 
 int /*<<< orphan*/  VMCI_MAKE_HANDLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCI_QUEUEPAIR_DETACH ; 
 int vmci_send_datagram (struct vmci_datagram*) ; 

int
vmci_queue_pair_detach_hypercall(struct vmci_handle handle)
{
	struct vmci_queue_pair_detach_msg detach_msg;

	detach_msg.hdr.dst = VMCI_MAKE_HANDLE(VMCI_HYPERVISOR_CONTEXT_ID,
	    VMCI_QUEUEPAIR_DETACH);
	detach_msg.hdr.src = VMCI_ANON_SRC_HANDLE;
	detach_msg.hdr.payload_size = sizeof(handle);
	detach_msg.handle = handle;

	return (vmci_send_datagram((struct vmci_datagram *)&detach_msg));
}