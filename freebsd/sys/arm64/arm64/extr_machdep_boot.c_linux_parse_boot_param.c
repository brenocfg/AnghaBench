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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fdt_header {int dummy; } ;
struct arm64_bootparams {scalar_t__ modulep; } ;

/* Variables and functions */
 int /*<<< orphan*/  fake_preload_metadata (struct fdt_header*,int /*<<< orphan*/ ,struct arm64_bootparams*) ; 
 scalar_t__ fdt_check_header (struct fdt_header*) ; 
 int /*<<< orphan*/  fdt_totalsize (struct fdt_header*) ; 

vm_offset_t
linux_parse_boot_param(struct arm64_bootparams *abp)
{
	uint32_t		dtb_size = 0;
	struct fdt_header	*dtb_ptr = NULL;

#if defined(FDT) && !defined(FDT_DTB_STATIC)
	/* Test if modulep (x0) point to valid DTB. */
	dtb_ptr = (struct fdt_header *)abp->modulep;
	if (dtb_ptr && fdt_check_header(dtb_ptr) == 0)
		dtb_size = fdt_totalsize(dtb_ptr);
#endif
	return (fake_preload_metadata(dtb_ptr, dtb_size, abp));
}