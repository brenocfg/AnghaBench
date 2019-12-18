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
typedef  int /*<<< orphan*/  vmci_privilege_flags ;
struct vmci_handle {int dummy; } ;
struct TYPE_2__ {scalar_t__ payload_size; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct vmci_doorbell_notify_msg {struct vmci_handle handle; TYPE_1__ hdr; } ;
struct vmci_datagram {int dummy; } ;
typedef  int /*<<< orphan*/  notify_msg ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_ANON_SRC_HANDLE ; 
 scalar_t__ VMCI_DG_HEADERSIZE ; 
 int /*<<< orphan*/  VMCI_DOORBELL_NOTIFY ; 
 int /*<<< orphan*/  VMCI_HYPERVISOR_CONTEXT_ID ; 
 int /*<<< orphan*/  VMCI_MAKE_HANDLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmci_send_datagram (struct vmci_datagram*) ; 

__attribute__((used)) static int
vmci_doorbell_notify_as_guest(struct vmci_handle handle,
    vmci_privilege_flags priv_flags)
{
	struct vmci_doorbell_notify_msg notify_msg;

	notify_msg.hdr.dst = VMCI_MAKE_HANDLE(VMCI_HYPERVISOR_CONTEXT_ID,
	    VMCI_DOORBELL_NOTIFY);
	notify_msg.hdr.src = VMCI_ANON_SRC_HANDLE;
	notify_msg.hdr.payload_size = sizeof(notify_msg) - VMCI_DG_HEADERSIZE;
	notify_msg.handle = handle;

	return (vmci_send_datagram((struct vmci_datagram *)&notify_msg));
}