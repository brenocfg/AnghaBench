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
struct fw_dump {scalar_t__ boot_mem_top; scalar_t__ kernel_metadata; scalar_t__ reserve_dump_area_size; scalar_t__ reserve_dump_area_start; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  OPAL_MPIPL_TAG_BOOT_MEM ; 
 int /*<<< orphan*/  OPAL_MPIPL_TAG_KERNEL ; 
 scalar_t__ OPAL_SUCCESS ; 
 int /*<<< orphan*/  __va (scalar_t__) ; 
 scalar_t__ opal_fadump_get_metadata_size () ; 
 int /*<<< orphan*/  opal_fadump_init_metadata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opal_fdm ; 
 scalar_t__ opal_mpipl_register_tag (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 

__attribute__((used)) static int opal_fadump_setup_metadata(struct fw_dump *fadump_conf)
{
	int err = 0;
	s64 ret;

	/*
	 * Use the last page(s) in FADump memory reservation for
	 * kernel metadata.
	 */
	fadump_conf->kernel_metadata = (fadump_conf->reserve_dump_area_start +
					fadump_conf->reserve_dump_area_size -
					opal_fadump_get_metadata_size());
	pr_info("Kernel metadata addr: %llx\n", fadump_conf->kernel_metadata);

	/* Initialize kernel metadata before registering the address with f/w */
	opal_fdm = __va(fadump_conf->kernel_metadata);
	opal_fadump_init_metadata(opal_fdm);

	/*
	 * Register metadata address with f/w. Can be retrieved in
	 * the capture kernel.
	 */
	ret = opal_mpipl_register_tag(OPAL_MPIPL_TAG_KERNEL,
				      fadump_conf->kernel_metadata);
	if (ret != OPAL_SUCCESS) {
		pr_err("Failed to set kernel metadata tag!\n");
		err = -EPERM;
	}

	/*
	 * Register boot memory top address with f/w. Should be retrieved
	 * by a kernel that intends to preserve crash'ed kernel's memory.
	 */
	ret = opal_mpipl_register_tag(OPAL_MPIPL_TAG_BOOT_MEM,
				      fadump_conf->boot_mem_top);
	if (ret != OPAL_SUCCESS) {
		pr_err("Failed to set boot memory tag!\n");
		err = -EPERM;
	}

	return err;
}