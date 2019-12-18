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
struct pt_regs {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 scalar_t__ pte_read (int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 
 int /*<<< orphan*/  va_kernel_present (unsigned long) ; 
 int /*<<< orphan*/  va_present (struct mm_struct*,unsigned long) ; 

int va_readable(struct pt_regs *regs, unsigned long addr)
{
	struct mm_struct *mm = current->mm;
	pte_t pte;
	int ret = 0;

	if (user_mode(regs)) {
		/* user mode */
		pte = va_present(mm, addr);
		if (!pte && pte_read(pte))
			ret = 1;
	} else {
		/* superuser mode is always readable, so we can only
		 * check it is present or not*/
		return (! !va_kernel_present(addr));
	}
	return ret;
}