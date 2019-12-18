#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct boot_e820_entry {unsigned long addr; scalar_t__ type; unsigned long size; } ;
struct TYPE_3__ {int /*<<< orphan*/  efi_loader_signature; } ;
struct TYPE_4__ {int e820_entries; struct boot_e820_entry* e820_table; TYPE_1__ efi_info; } ;

/* Variables and functions */
 unsigned long BIOS_START_MAX ; 
 unsigned long BIOS_START_MIN ; 
 scalar_t__ E820_TYPE_RAM ; 
 int /*<<< orphan*/  EFI32_LOADER_SIGNATURE ; 
 int /*<<< orphan*/  EFI64_LOADER_SIGNATURE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned long TRAMPOLINE_32BIT_SIZE ; 
 TYPE_2__* boot_params ; 
 unsigned long round_down (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned long find_trampoline_placement(void)
{
	unsigned long bios_start = 0, ebda_start = 0;
	struct boot_e820_entry *entry;
	char *signature;
	int i;

	/*
	 * Find a suitable spot for the trampoline.
	 * This code is based on reserve_bios_regions().
	 */

	/*
	 * EFI systems may not provide legacy ROM. The memory may not be mapped
	 * at all.
	 *
	 * Only look for values in the legacy ROM for non-EFI system.
	 */
	signature = (char *)&boot_params->efi_info.efi_loader_signature;
	if (strncmp(signature, EFI32_LOADER_SIGNATURE, 4) &&
	    strncmp(signature, EFI64_LOADER_SIGNATURE, 4)) {
		ebda_start = *(unsigned short *)0x40e << 4;
		bios_start = *(unsigned short *)0x413 << 10;
	}

	if (bios_start < BIOS_START_MIN || bios_start > BIOS_START_MAX)
		bios_start = BIOS_START_MAX;

	if (ebda_start > BIOS_START_MIN && ebda_start < bios_start)
		bios_start = ebda_start;

	bios_start = round_down(bios_start, PAGE_SIZE);

	/* Find the first usable memory region under bios_start. */
	for (i = boot_params->e820_entries - 1; i >= 0; i--) {
		unsigned long new = bios_start;

		entry = &boot_params->e820_table[i];

		/* Skip all entries above bios_start. */
		if (bios_start <= entry->addr)
			continue;

		/* Skip non-RAM entries. */
		if (entry->type != E820_TYPE_RAM)
			continue;

		/* Adjust bios_start to the end of the entry if needed. */
		if (bios_start > entry->addr + entry->size)
			new = entry->addr + entry->size;

		/* Keep bios_start page-aligned. */
		new = round_down(new, PAGE_SIZE);

		/* Skip the entry if it's too small. */
		if (new - TRAMPOLINE_32BIT_SIZE < entry->addr)
			continue;

		/* Protect against underflow. */
		if (new - TRAMPOLINE_32BIT_SIZE > bios_start)
			break;

		bios_start = new;
		break;
	}

	/* Place the trampoline just below the end of low memory */
	return bios_start - TRAMPOLINE_32BIT_SIZE;
}