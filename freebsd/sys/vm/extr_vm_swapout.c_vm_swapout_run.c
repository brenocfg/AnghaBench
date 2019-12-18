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

/* Variables and functions */
 int /*<<< orphan*/  VM_SWAP_NORMAL ; 
 int /*<<< orphan*/  vm_req_vmdaemon (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_swap_enabled ; 

void
vm_swapout_run(void)
{

	if (vm_swap_enabled)
		vm_req_vmdaemon(VM_SWAP_NORMAL);
}