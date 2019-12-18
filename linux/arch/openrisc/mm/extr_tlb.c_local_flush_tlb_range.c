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
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  flush_dtlb_page_eir (int) ; 
 int /*<<< orphan*/  flush_dtlb_page_no_eir (int) ; 
 int /*<<< orphan*/  flush_itlb_page_eir (int) ; 
 int /*<<< orphan*/  flush_itlb_page_no_eir (int) ; 
 int have_dtlbeir ; 
 int have_itlbeir ; 

void local_flush_tlb_range(struct vm_area_struct *vma,
			   unsigned long start, unsigned long end)
{
	int addr;
	bool dtlbeir;
	bool itlbeir;

	dtlbeir = have_dtlbeir;
	itlbeir = have_itlbeir;

	for (addr = start; addr < end; addr += PAGE_SIZE) {
		if (dtlbeir)
			flush_dtlb_page_eir(addr);
		else
			flush_dtlb_page_no_eir(addr);

		if (itlbeir)
			flush_itlb_page_eir(addr);
		else
			flush_itlb_page_no_eir(addr);
	}
}