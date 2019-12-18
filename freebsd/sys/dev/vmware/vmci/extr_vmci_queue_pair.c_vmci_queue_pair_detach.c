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
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 scalar_t__ VMCI_HANDLE_INVALID (struct vmci_handle) ; 
 int vmci_queue_pair_detach_guest_work (struct vmci_handle) ; 

int
vmci_queue_pair_detach(struct vmci_handle handle)
{

	if (VMCI_HANDLE_INVALID(handle))
		return (VMCI_ERROR_INVALID_ARGS);

	return (vmci_queue_pair_detach_guest_work(handle));
}