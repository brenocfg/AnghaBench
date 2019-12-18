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
struct mm_struct {int dummy; } ;
struct flush_tlb_page_struct {int /*<<< orphan*/  addr; int /*<<< orphan*/  vma; struct mm_struct* mm; } ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  asn_locked () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  flush_tlb_current_page (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_other (struct mm_struct*) ; 

__attribute__((used)) static void
ipi_flush_tlb_page(void *x)
{
	struct flush_tlb_page_struct *data = (struct flush_tlb_page_struct *)x;
	struct mm_struct * mm = data->mm;

	if (mm == current->active_mm && !asn_locked())
		flush_tlb_current_page(mm, data->vma, data->addr);
	else
		flush_tlb_other(mm);
}