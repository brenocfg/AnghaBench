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
 int /*<<< orphan*/ * __xive_vm_h_cppr ; 
 int /*<<< orphan*/ * __xive_vm_h_eoi ; 
 int /*<<< orphan*/ * __xive_vm_h_ipi ; 
 int /*<<< orphan*/ * __xive_vm_h_ipoll ; 
 int /*<<< orphan*/ * __xive_vm_h_xirr ; 

void kvmppc_xive_exit_module(void)
{
	__xive_vm_h_xirr = NULL;
	__xive_vm_h_ipoll = NULL;
	__xive_vm_h_ipi = NULL;
	__xive_vm_h_cppr = NULL;
	__xive_vm_h_eoi = NULL;
}