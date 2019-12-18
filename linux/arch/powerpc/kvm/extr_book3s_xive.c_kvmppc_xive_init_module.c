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
 int /*<<< orphan*/  __xive_vm_h_cppr ; 
 int /*<<< orphan*/  __xive_vm_h_eoi ; 
 int /*<<< orphan*/  __xive_vm_h_ipi ; 
 int /*<<< orphan*/  __xive_vm_h_ipoll ; 
 int /*<<< orphan*/  __xive_vm_h_xirr ; 
 int /*<<< orphan*/  xive_vm_h_cppr ; 
 int /*<<< orphan*/  xive_vm_h_eoi ; 
 int /*<<< orphan*/  xive_vm_h_ipi ; 
 int /*<<< orphan*/  xive_vm_h_ipoll ; 
 int /*<<< orphan*/  xive_vm_h_xirr ; 

void kvmppc_xive_init_module(void)
{
	__xive_vm_h_xirr = xive_vm_h_xirr;
	__xive_vm_h_ipoll = xive_vm_h_ipoll;
	__xive_vm_h_ipi = xive_vm_h_ipi;
	__xive_vm_h_cppr = xive_vm_h_cppr;
	__xive_vm_h_eoi = xive_vm_h_eoi;
}