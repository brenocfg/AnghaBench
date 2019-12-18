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
 scalar_t__ BOOT_HEAP_SIZE ; 
 int /*<<< orphan*/  CONFIG_MIPS_RAW_APPENDED_DTB ; 
 scalar_t__ FDT_MAGIC ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned long VMLINUX_LOAD_ADDRESS_ULL ; 
 int /*<<< orphan*/  __appended_dtb ; 
 int /*<<< orphan*/  __decompress (char*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __image_begin ; 
 int /*<<< orphan*/  __image_end ; 
 int /*<<< orphan*/  error ; 
 scalar_t__ fdt_magic (void*) ; 
 unsigned int fdt_totalsize (void*) ; 
 scalar_t__ free_mem_end_ptr ; 
 unsigned long free_mem_ptr ; 
 unsigned int le32_to_cpup (void*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  puthex (unsigned long) ; 
 int /*<<< orphan*/  puts (char*) ; 

void decompress_kernel(unsigned long boot_heap_start)
{
	unsigned long zimage_start, zimage_size;

	zimage_start = (unsigned long)(&__image_begin);
	zimage_size = (unsigned long)(&__image_end) -
	    (unsigned long)(&__image_begin);

	puts("zimage at:     ");
	puthex(zimage_start);
	puts(" ");
	puthex(zimage_size + zimage_start);
	puts("\n");

	/* This area are prepared for mallocing when decompressing */
	free_mem_ptr = boot_heap_start;
	free_mem_end_ptr = boot_heap_start + BOOT_HEAP_SIZE;

	/* Display standard Linux/MIPS boot prompt */
	puts("Uncompressing Linux at load address ");
	puthex(VMLINUX_LOAD_ADDRESS_ULL);
	puts("\n");

	/* Decompress the kernel with according algorithm */
	__decompress((char *)zimage_start, zimage_size, 0, 0,
		   (void *)VMLINUX_LOAD_ADDRESS_ULL, 0, 0, error);

	if (IS_ENABLED(CONFIG_MIPS_RAW_APPENDED_DTB) &&
	    fdt_magic((void *)&__appended_dtb) == FDT_MAGIC) {
		unsigned int image_size, dtb_size;

		dtb_size = fdt_totalsize((void *)&__appended_dtb);

		/* last four bytes is always image size in little endian */
		image_size = le32_to_cpup((void *)&__image_end - 4);

		/* copy dtb to where the booted kernel will expect it */
		memcpy((void *)VMLINUX_LOAD_ADDRESS_ULL + image_size,
		       __appended_dtb, dtb_size);
	}

	/* FIXME: should we flush cache here? */
	puts("Now, booting the kernel...\n");
}