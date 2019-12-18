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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPI_AST ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int VMM_CLEANUP () ; 
 int /*<<< orphan*/  iommu_cleanup () ; 
 int /*<<< orphan*/  lapic_ipi_free (int /*<<< orphan*/ ) ; 
 int vmm_init () ; 
 int vmm_initialized ; 
 int /*<<< orphan*/  vmm_ipinum ; 
 int /*<<< orphan*/ * vmm_resume_p ; 
 int vmmdev_cleanup () ; 
 int /*<<< orphan*/  vmmdev_init () ; 

__attribute__((used)) static int
vmm_handler(module_t mod, int what, void *arg)
{
	int error;

	switch (what) {
	case MOD_LOAD:
		vmmdev_init();
		error = vmm_init();
		if (error == 0)
			vmm_initialized = 1;
		break;
	case MOD_UNLOAD:
		error = vmmdev_cleanup();
		if (error == 0) {
			vmm_resume_p = NULL;
			iommu_cleanup();
			if (vmm_ipinum != IPI_AST)
				lapic_ipi_free(vmm_ipinum);
			error = VMM_CLEANUP();
			/*
			 * Something bad happened - prevent new
			 * VMs from being created
			 */
			if (error)
				vmm_initialized = 0;
		}
		break;
	default:
		error = 0;
		break;
	}
	return (error);
}