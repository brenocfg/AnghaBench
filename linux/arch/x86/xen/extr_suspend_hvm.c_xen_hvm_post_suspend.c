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
 int /*<<< orphan*/  xen_callback_vector () ; 
 int /*<<< orphan*/  xen_hvm_init_shared_info () ; 
 int /*<<< orphan*/  xen_unplug_emulated_devices () ; 
 int /*<<< orphan*/  xen_vcpu_restore () ; 

void xen_hvm_post_suspend(int suspend_cancelled)
{
	if (!suspend_cancelled) {
		xen_hvm_init_shared_info();
		xen_vcpu_restore();
	}
	xen_callback_vector();
	xen_unplug_emulated_devices();
}