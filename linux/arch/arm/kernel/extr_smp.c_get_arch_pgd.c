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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long __phys_to_pfn (unsigned long) ; 
 unsigned long virt_to_phys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long get_arch_pgd(pgd_t *pgd)
{
#ifdef CONFIG_ARM_LPAE
	return __phys_to_pfn(virt_to_phys(pgd));
#else
	return virt_to_phys(pgd);
#endif
}