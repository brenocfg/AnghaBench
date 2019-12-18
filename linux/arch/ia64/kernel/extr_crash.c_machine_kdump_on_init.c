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
 int /*<<< orphan*/  crash_save_vmcoreinfo () ; 
 int /*<<< orphan*/  ia64_kimage ; 
 int /*<<< orphan*/  kexec_disable_iosapic () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  machine_kexec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
machine_kdump_on_init(void)
{
	crash_save_vmcoreinfo();
	local_irq_disable();
	kexec_disable_iosapic();
	machine_kexec(ia64_kimage);
}