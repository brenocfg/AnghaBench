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
struct bios_smap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_smap_entry (struct bios_smap*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
add_smap_entries(struct bios_smap *smapbase, vm_paddr_t *physmap,
    int *physmap_idxp)
{
	struct bios_smap *smap, *smapend;
	u_int32_t smapsize;
	/*
	 * Memory map from INT 15:E820.
	 *
	 * subr_module.c says:
	 * "Consumer may safely assume that size value precedes data."
	 * ie: an int32_t immediately precedes SMAP.
	 */
	smapsize = *((u_int32_t *)smapbase - 1);
	smapend = (struct bios_smap *)((uintptr_t)smapbase + smapsize);

	for (smap = smapbase; smap < smapend; smap++)
		if (!add_smap_entry(smap, physmap, physmap_idxp))
			break;
}