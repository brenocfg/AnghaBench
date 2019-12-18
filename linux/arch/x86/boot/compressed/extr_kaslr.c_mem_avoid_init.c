#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {unsigned long init_size; int ramdisk_image; int ramdisk_size; int cmd_line_ptr; } ;
struct TYPE_6__ {TYPE_1__ hdr; scalar_t__ ext_cmd_line_ptr; scalar_t__ ext_ramdisk_size; scalar_t__ ext_ramdisk_image; } ;
struct TYPE_5__ {unsigned long start; unsigned long size; } ;

/* Variables and functions */
 size_t MEM_AVOID_BOOTPARAMS ; 
 size_t MEM_AVOID_CMDLINE ; 
 size_t MEM_AVOID_INITRD ; 
 size_t MEM_AVOID_ZO_RANGE ; 
 unsigned long PMD_SIZE ; 
 int /*<<< orphan*/  add_identity_map (unsigned long,unsigned long) ; 
 TYPE_3__* boot_params ; 
 int /*<<< orphan*/  count_immovable_mem_regions () ; 
 int /*<<< orphan*/  handle_mem_options () ; 
 TYPE_2__* mem_avoid ; 
 int /*<<< orphan*/  num_immovable_mem ; 

__attribute__((used)) static void mem_avoid_init(unsigned long input, unsigned long input_size,
			   unsigned long output)
{
	unsigned long init_size = boot_params->hdr.init_size;
	u64 initrd_start, initrd_size;
	u64 cmd_line, cmd_line_size;
	char *ptr;

	/*
	 * Avoid the region that is unsafe to overlap during
	 * decompression.
	 */
	mem_avoid[MEM_AVOID_ZO_RANGE].start = input;
	mem_avoid[MEM_AVOID_ZO_RANGE].size = (output + init_size) - input;
	add_identity_map(mem_avoid[MEM_AVOID_ZO_RANGE].start,
			 mem_avoid[MEM_AVOID_ZO_RANGE].size);

	/* Avoid initrd. */
	initrd_start  = (u64)boot_params->ext_ramdisk_image << 32;
	initrd_start |= boot_params->hdr.ramdisk_image;
	initrd_size  = (u64)boot_params->ext_ramdisk_size << 32;
	initrd_size |= boot_params->hdr.ramdisk_size;
	mem_avoid[MEM_AVOID_INITRD].start = initrd_start;
	mem_avoid[MEM_AVOID_INITRD].size = initrd_size;
	/* No need to set mapping for initrd, it will be handled in VO. */

	/* Avoid kernel command line. */
	cmd_line  = (u64)boot_params->ext_cmd_line_ptr << 32;
	cmd_line |= boot_params->hdr.cmd_line_ptr;
	/* Calculate size of cmd_line. */
	ptr = (char *)(unsigned long)cmd_line;
	for (cmd_line_size = 0; ptr[cmd_line_size++];)
		;
	mem_avoid[MEM_AVOID_CMDLINE].start = cmd_line;
	mem_avoid[MEM_AVOID_CMDLINE].size = cmd_line_size;
	add_identity_map(mem_avoid[MEM_AVOID_CMDLINE].start,
			 mem_avoid[MEM_AVOID_CMDLINE].size);

	/* Avoid boot parameters. */
	mem_avoid[MEM_AVOID_BOOTPARAMS].start = (unsigned long)boot_params;
	mem_avoid[MEM_AVOID_BOOTPARAMS].size = sizeof(*boot_params);
	add_identity_map(mem_avoid[MEM_AVOID_BOOTPARAMS].start,
			 mem_avoid[MEM_AVOID_BOOTPARAMS].size);

	/* We don't need to set a mapping for setup_data. */

	/* Mark the memmap regions we need to avoid */
	handle_mem_options();

	/* Enumerate the immovable memory regions */
	num_immovable_mem = count_immovable_mem_regions();

#ifdef CONFIG_X86_VERBOSE_BOOTUP
	/* Make sure video RAM can be used. */
	add_identity_map(0, PMD_SIZE);
#endif
}