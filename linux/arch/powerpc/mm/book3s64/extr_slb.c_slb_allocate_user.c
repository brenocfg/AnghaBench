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
struct mm_struct {int /*<<< orphan*/  context; } ;
struct TYPE_2__ {unsigned long sllp; } ;

/* Variables and functions */
 long EFAULT ; 
 unsigned long H_PGTABLE_RANGE ; 
 unsigned long SLB_VSID_USER ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int get_slice_psize (struct mm_struct*,unsigned long) ; 
 unsigned long get_user_context (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long mm_ctx_slb_addr_limit (int /*<<< orphan*/ *) ; 
 TYPE_1__* mmu_psize_defs ; 
 long slb_insert_entry (unsigned long,unsigned long,unsigned long,int,int) ; 
 scalar_t__ unlikely (int) ; 
 int user_segment_size (unsigned long) ; 

__attribute__((used)) static long slb_allocate_user(struct mm_struct *mm, unsigned long ea)
{
	unsigned long context;
	unsigned long flags;
	int bpsize;
	int ssize;

	/*
	 * consider this as bad access if we take a SLB miss
	 * on an address above addr limit.
	 */
	if (ea >= mm_ctx_slb_addr_limit(&mm->context))
		return -EFAULT;

	context = get_user_context(&mm->context, ea);
	if (!context)
		return -EFAULT;

	if (unlikely(ea >= H_PGTABLE_RANGE)) {
		WARN_ON(1);
		return -EFAULT;
	}

	ssize = user_segment_size(ea);

	bpsize = get_slice_psize(mm, ea);
	flags = SLB_VSID_USER | mmu_psize_defs[bpsize].sllp;

	return slb_insert_entry(ea, context, flags, ssize, false);
}