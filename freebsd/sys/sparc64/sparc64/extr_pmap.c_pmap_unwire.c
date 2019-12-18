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
typedef  scalar_t__ vm_offset_t ;
struct tte {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ PMAP_TSB_THRESH ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_unwire_tte (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tte*,scalar_t__) ; 
 int /*<<< orphan*/  tsb_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tte*,scalar_t__)) ; 
 struct tte* tsb_tte_lookup (int /*<<< orphan*/ ,scalar_t__) ; 

void
pmap_unwire(pmap_t pm, vm_offset_t sva, vm_offset_t eva)
{
	vm_offset_t va;
	struct tte *tp;

	PMAP_LOCK(pm);
	if (eva - sva > PMAP_TSB_THRESH)
		tsb_foreach(pm, NULL, sva, eva, pmap_unwire_tte);
	else {
		for (va = sva; va < eva; va += PAGE_SIZE)
			if ((tp = tsb_tte_lookup(pm, va)) != NULL)
				pmap_unwire_tte(pm, NULL, tp, va);
	}
	PMAP_UNLOCK(pm);
}