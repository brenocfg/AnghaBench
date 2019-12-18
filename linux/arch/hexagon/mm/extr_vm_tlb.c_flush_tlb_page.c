#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct TYPE_5__ {scalar_t__ ptbase; } ;
struct mm_struct {TYPE_1__ context; } ;
struct TYPE_8__ {TYPE_3__* active_mm; } ;
struct TYPE_6__ {scalar_t__ ptbase; } ;
struct TYPE_7__ {TYPE_2__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __vmclrmap (void*,int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 

void flush_tlb_page(struct vm_area_struct *vma, unsigned long vaddr)
{
	struct mm_struct *mm = vma->vm_mm;

	if (mm->context.ptbase  == current->active_mm->context.ptbase)
		__vmclrmap((void *)vaddr, PAGE_SIZE);
}