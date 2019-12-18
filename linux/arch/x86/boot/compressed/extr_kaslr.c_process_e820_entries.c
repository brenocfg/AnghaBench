#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mem_vector {int /*<<< orphan*/  size; int /*<<< orphan*/  start; } ;
struct boot_e820_entry {scalar_t__ type; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int e820_entries; struct boot_e820_entry* e820_table; } ;

/* Variables and functions */
 scalar_t__ E820_TYPE_RAM ; 
 TYPE_1__* boot_params ; 
 scalar_t__ process_mem_region (struct mem_vector*,unsigned long,unsigned long) ; 

__attribute__((used)) static void process_e820_entries(unsigned long minimum,
				 unsigned long image_size)
{
	int i;
	struct mem_vector region;
	struct boot_e820_entry *entry;

	/* Verify potential e820 positions, appending to slots list. */
	for (i = 0; i < boot_params->e820_entries; i++) {
		entry = &boot_params->e820_table[i];
		/* Skip non-RAM entries. */
		if (entry->type != E820_TYPE_RAM)
			continue;
		region.start = entry->addr;
		region.size = entry->size;
		if (process_mem_region(&region, minimum, image_size))
			break;
	}
}