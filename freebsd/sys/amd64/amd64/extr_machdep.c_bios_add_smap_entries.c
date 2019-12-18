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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  scalar_t__ u_int32_t ;
struct bios_smap {int type; int /*<<< orphan*/  length; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int RB_VERBOSE ; 
 scalar_t__ SMAP_TYPE_MEMORY ; 
 int /*<<< orphan*/  add_physmap_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int boothowto ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bios_add_smap_entries(struct bios_smap *smapbase, u_int32_t smapsize,
                      vm_paddr_t *physmap, int *physmap_idx)
{
	struct bios_smap *smap, *smapend;

	smapend = (struct bios_smap *)((uintptr_t)smapbase + smapsize);

	for (smap = smapbase; smap < smapend; smap++) {
		if (boothowto & RB_VERBOSE)
			printf("SMAP type=%02x base=%016lx len=%016lx\n",
			    smap->type, smap->base, smap->length);

		if (smap->type != SMAP_TYPE_MEMORY)
			continue;

		if (!add_physmap_entry(smap->base, smap->length, physmap,
		    physmap_idx))
			break;
	}
}