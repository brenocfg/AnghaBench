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
 scalar_t__ fdt_is_setup () ; 
 int /*<<< orphan*/  fdt_setup_fdtp () ; 

int
efi_autoload(void)
{

#if defined(LOADER_FDT_SUPPORT)
	/*
	 * Setup the FDT early so that we're not loading files during bi_load.
	 * Any such loading is inherently broken since bi_load uses the space
	 * just after all currently loaded files for the data that will be
	 * passed to the kernel and newly loaded files will be positioned in
	 * that same space.
	 *
	 * We're glossing over errors here because LOADER_FDT_SUPPORT does not
	 * imply that we're on a platform where FDT is a requirement.  If we
	 * fix this, then the error handling here should be fixed accordingly.
	 */
	if (fdt_is_setup() == 0)
		fdt_setup_fdtp();
#endif
	return (0);
}