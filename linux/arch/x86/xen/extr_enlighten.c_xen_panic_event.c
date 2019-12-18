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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  SHUTDOWN_crash ; 
 int /*<<< orphan*/  kexec_crash_loaded () ; 
 int panic_timeout ; 
 int /*<<< orphan*/  reboot_reason ; 
 scalar_t__ xen_legacy_crash ; 
 int /*<<< orphan*/  xen_reboot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xen_panic_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	if (!kexec_crash_loaded()) {
		if (xen_legacy_crash)
			xen_reboot(SHUTDOWN_crash);

		reboot_reason = SHUTDOWN_crash;

		/*
		 * If panic_timeout==0 then we are supposed to wait forever.
		 * However, to preserve original dom0 behavior we have to drop
		 * into hypervisor. (domU behavior is controlled by its
		 * config file)
		 */
		if (panic_timeout == 0)
			panic_timeout = -1;
	}
	return NOTIFY_DONE;
}