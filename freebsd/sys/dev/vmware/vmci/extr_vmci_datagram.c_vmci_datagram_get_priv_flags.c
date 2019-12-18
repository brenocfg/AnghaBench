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
struct vmci_handle {scalar_t__ context; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 scalar_t__ VMCI_INVALID_ID ; 
 int vmci_datagram_get_priv_flags_int (scalar_t__,struct vmci_handle,int /*<<< orphan*/ *) ; 

int
vmci_datagram_get_priv_flags(struct vmci_handle handle,
    vmci_privilege_flags *priv_flags)
{

	if (priv_flags == NULL || handle.context == VMCI_INVALID_ID)
		return (VMCI_ERROR_INVALID_ARGS);

	return (vmci_datagram_get_priv_flags_int(handle.context, handle,
	    priv_flags));
}