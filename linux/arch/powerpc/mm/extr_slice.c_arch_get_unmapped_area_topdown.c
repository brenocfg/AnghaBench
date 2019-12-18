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
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  mm_ctx_user_psize (int /*<<< orphan*/ *) ; 
 unsigned long slice_get_unmapped_area (unsigned long const,unsigned long const,unsigned long const,int /*<<< orphan*/ ,int) ; 

unsigned long arch_get_unmapped_area_topdown(struct file *filp,
					     const unsigned long addr0,
					     const unsigned long len,
					     const unsigned long pgoff,
					     const unsigned long flags)
{
	return slice_get_unmapped_area(addr0, len, flags,
				       mm_ctx_user_psize(&current->mm->context), 1);
}