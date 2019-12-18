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
 scalar_t__ bootverbose ; 
 int msix_disable_migration ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
hypervisor_quirks(unsigned int major, unsigned int minor)
{
#ifdef SMP
	if (((major < 4) || (major == 4 && minor <= 5)) &&
	    msix_disable_migration == -1) {
		/*
		 * Xen hypervisors prior to 4.6.0 do not properly
		 * handle updates to enabled MSI-X table entries,
		 * so disable MSI-X interrupt migration in that
		 * case.
		 */
		if (bootverbose)
			printf(
"Disabling MSI-X interrupt migration due to Xen hypervisor bug.\n"
"Set machdep.msix_disable_migration=0 to forcefully enable it.\n");
		msix_disable_migration = 1;
	}
#endif
}