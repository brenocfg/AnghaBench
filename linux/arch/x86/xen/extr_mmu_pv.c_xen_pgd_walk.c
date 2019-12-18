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
struct mm_struct {int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 int __xen_pgd_walk (struct mm_struct*,int /*<<< orphan*/ ,int (*) (struct mm_struct*,struct page*,int),unsigned long) ; 

__attribute__((used)) static int xen_pgd_walk(struct mm_struct *mm,
			int (*func)(struct mm_struct *mm, struct page *,
				    enum pt_level),
			unsigned long limit)
{
	return __xen_pgd_walk(mm, mm->pgd, func, limit);
}