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
typedef  int vmci_privilege_flags ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 scalar_t__ VMCI_HANDLE_INVALID (struct vmci_handle) ; 
 struct vmci_handle VMCI_INVALID_HANDLE ; 
 int VMCI_PRIVILEGE_ALL_FLAGS ; 
 int vmci_doorbell_notify_as_guest (struct vmci_handle,int) ; 

int
vmci_doorbell_notify(struct vmci_handle dst, vmci_privilege_flags priv_flags)
{
	struct vmci_handle src;

	if (VMCI_HANDLE_INVALID(dst) ||
	    (priv_flags & ~VMCI_PRIVILEGE_ALL_FLAGS))
		return (VMCI_ERROR_INVALID_ARGS);

	src = VMCI_INVALID_HANDLE;

	return (vmci_doorbell_notify_as_guest(dst, priv_flags));
}