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
struct fdt_header {int dummy; } ;

/* Variables and functions */
 struct fdt_header* efi_get_table (int /*<<< orphan*/ *) ; 
 scalar_t__ fdt_load_dtb_addr (struct fdt_header*) ; 
 int /*<<< orphan*/  fdtdtb ; 
 int /*<<< orphan*/  printf (char*,struct fdt_header*) ; 

int
fdt_platform_load_dtb(void)
{
	struct fdt_header *hdr;

	hdr = efi_get_table(&fdtdtb);
	if (hdr == NULL)
		return (1);
	if (fdt_load_dtb_addr(hdr) != 0)
		return (1);
	printf("Using DTB provided by EFI at %p.\n", hdr);

	return (0);
}