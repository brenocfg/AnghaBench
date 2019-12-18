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
 unsigned long __pa_symbol (int /*<<< orphan*/ ) ; 
 struct mm_struct init_mm ; 
 scalar_t__ virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long mm_to_pgd_phys(struct mm_struct *mm)
{
	/* Either init_pg_dir or swapper_pg_dir */
	if (mm == &init_mm)
		return __pa_symbol(mm->pgd);

	return (unsigned long)virt_to_phys(mm->pgd);
}