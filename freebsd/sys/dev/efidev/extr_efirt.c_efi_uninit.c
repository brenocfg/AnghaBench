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
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * efi_cfgtbl ; 
 int /*<<< orphan*/  efi_destroy_1t1_map () ; 
 int /*<<< orphan*/  efi_lock ; 
 int /*<<< orphan*/ * efi_runtime ; 
 int /*<<< orphan*/ * efi_shutdown_tag ; 
 int /*<<< orphan*/ * efi_systbl ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown_final ; 

__attribute__((used)) static void
efi_uninit(void)
{

	/* Most likely disabled by tunable */
	if (efi_runtime == NULL)
		return;
	if (efi_shutdown_tag != NULL)
		EVENTHANDLER_DEREGISTER(shutdown_final, efi_shutdown_tag);
	efi_destroy_1t1_map();

	efi_systbl = NULL;
	efi_cfgtbl = NULL;
	efi_runtime = NULL;

	mtx_destroy(&efi_lock);
}