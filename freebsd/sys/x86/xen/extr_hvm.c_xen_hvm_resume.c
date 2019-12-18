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
 int /*<<< orphan*/  XEN_HVM_INIT_CANCELLED_SUSPEND ; 
 int /*<<< orphan*/  XEN_HVM_INIT_RESUME ; 
 int /*<<< orphan*/  xen_hvm_cpu_init () ; 
 int /*<<< orphan*/  xen_hvm_init (int /*<<< orphan*/ ) ; 

void
xen_hvm_resume(bool suspend_cancelled)
{

	xen_hvm_init(suspend_cancelled ?
	    XEN_HVM_INIT_CANCELLED_SUSPEND : XEN_HVM_INIT_RESUME);

	/* Register vcpu_info area for CPU#0. */
	xen_hvm_cpu_init();
}