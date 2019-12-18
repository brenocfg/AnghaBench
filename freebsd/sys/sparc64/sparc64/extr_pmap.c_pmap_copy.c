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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
struct tte {int dummy; } ;
typedef  scalar_t__ pmap_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK (scalar_t__) ; 
 scalar_t__ PMAP_TSB_THRESH ; 
 int /*<<< orphan*/  PMAP_UNLOCK (scalar_t__) ; 
 int /*<<< orphan*/  pmap_copy_tte (scalar_t__,scalar_t__,struct tte*,scalar_t__) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlb_context_demap (scalar_t__) ; 
 int /*<<< orphan*/  tlb_range_demap (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tsb_foreach (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/  (*) (scalar_t__,scalar_t__,struct tte*,scalar_t__)) ; 
 struct tte* tsb_tte_lookup (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tte_list_global_lock ; 

void
pmap_copy(pmap_t dst_pmap, pmap_t src_pmap, vm_offset_t dst_addr,
    vm_size_t len, vm_offset_t src_addr)
{
	struct tte *tp;
	vm_offset_t va;

	if (dst_addr != src_addr)
		return;
	rw_wlock(&tte_list_global_lock);
	if (dst_pmap < src_pmap) {
		PMAP_LOCK(dst_pmap);
		PMAP_LOCK(src_pmap);
	} else {
		PMAP_LOCK(src_pmap);
		PMAP_LOCK(dst_pmap);
	}
	if (len > PMAP_TSB_THRESH) {
		tsb_foreach(src_pmap, dst_pmap, src_addr, src_addr + len,
		    pmap_copy_tte);
		tlb_context_demap(dst_pmap);
	} else {
		for (va = src_addr; va < src_addr + len; va += PAGE_SIZE)
			if ((tp = tsb_tte_lookup(src_pmap, va)) != NULL)
				pmap_copy_tte(src_pmap, dst_pmap, tp, va);
		tlb_range_demap(dst_pmap, src_addr, src_addr + len - 1);
	}
	rw_wunlock(&tte_list_global_lock);
	PMAP_UNLOCK(src_pmap);
	PMAP_UNLOCK(dst_pmap);
}