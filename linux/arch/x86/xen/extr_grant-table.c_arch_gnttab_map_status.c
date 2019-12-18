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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  grant_status_t ;
struct TYPE_4__ {int /*<<< orphan*/ * ptes; TYPE_1__* area; } ;
struct TYPE_3__ {int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 TYPE_2__ gnttab_status_vm_area ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  mfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int arch_gnttab_map_status(uint64_t *frames, unsigned long nr_gframes,
			   unsigned long max_nr_gframes,
			   grant_status_t **__shared)
{
	grant_status_t *shared = *__shared;
	unsigned long addr;
	unsigned long i;

	if (shared == NULL)
		*__shared = shared = gnttab_status_vm_area.area->addr;

	addr = (unsigned long)shared;

	for (i = 0; i < nr_gframes; i++) {
		set_pte_at(&init_mm, addr, gnttab_status_vm_area.ptes[i],
			   mfn_pte(frames[i], PAGE_KERNEL));
		addr += PAGE_SIZE;
	}

	return 0;
}