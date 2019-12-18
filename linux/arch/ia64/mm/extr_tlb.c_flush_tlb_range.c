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
struct vm_area_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ REGION_NUMBER (unsigned long) ; 
 int /*<<< orphan*/  __flush_tlb_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 unsigned long ia64_thash (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void flush_tlb_range(struct vm_area_struct *vma,
		unsigned long start, unsigned long end)
{
	if (unlikely(end - start >= 1024*1024*1024*1024UL
			|| REGION_NUMBER(start) != REGION_NUMBER(end - 1))) {
		/*
		 * If we flush more than a tera-byte or across regions, we're
		 * probably better off just flushing the entire TLB(s).  This
		 * should be very rare and is not worth optimizing for.
		 */
		flush_tlb_all();
	} else {
		/* flush the address range from the tlb */
		__flush_tlb_range(vma, start, end);
		/* flush the virt. page-table area mapping the addr range */
		__flush_tlb_range(vma, ia64_thash(start), ia64_thash(end));
	}
}