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
typedef  int /*<<< orphan*/  uint8_t ;
struct efi_md {int dummy; } ;
struct efi_map_header {int descriptor_size; int memory_size; } ;
typedef  int /*<<< orphan*/  (* efi_map_entry_cb ) (struct efi_md*) ;

/* Variables and functions */
 struct efi_md* efi_next_descriptor (struct efi_md*,int) ; 

__attribute__((used)) static void
foreach_efi_map_entry(struct efi_map_header *efihdr, efi_map_entry_cb cb)
{
	struct efi_md *map, *p;
	size_t efisz;
	int ndesc, i;

	/*
	 * Memory map data provided by UEFI via the GetMemoryMap
	 * Boot Services API.
	 */
	efisz = (sizeof(struct efi_map_header) + 0xf) & ~0xf;
	map = (struct efi_md *)((uint8_t *)efihdr + efisz); 

	if (efihdr->descriptor_size == 0)
		return;
	ndesc = efihdr->memory_size / efihdr->descriptor_size;

	for (i = 0, p = map; i < ndesc; i++,
	    p = efi_next_descriptor(p, efihdr->descriptor_size)) {
		cb(p);
	}
}