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

/* Variables and functions */
 unsigned long KERNBASE ; 
 unsigned long kern_base ; 
 int /*<<< orphan*/  patch_one_ktsb_phys (unsigned int*,unsigned int*,unsigned long) ; 
 int /*<<< orphan*/ * swapper_4m_tsb ; 
 int /*<<< orphan*/ * swapper_tsb ; 

__attribute__((used)) static void ktsb_phys_patch(void)
{
	extern unsigned int __swapper_tsb_phys_patch;
	extern unsigned int __swapper_tsb_phys_patch_end;
	unsigned long ktsb_pa;

	ktsb_pa = kern_base + ((unsigned long)&swapper_tsb[0] - KERNBASE);
	patch_one_ktsb_phys(&__swapper_tsb_phys_patch,
			    &__swapper_tsb_phys_patch_end, ktsb_pa);
#ifndef CONFIG_DEBUG_PAGEALLOC
	{
	extern unsigned int __swapper_4m_tsb_phys_patch;
	extern unsigned int __swapper_4m_tsb_phys_patch_end;
	ktsb_pa = (kern_base +
		   ((unsigned long)&swapper_4m_tsb[0] - KERNBASE));
	patch_one_ktsb_phys(&__swapper_4m_tsb_phys_patch,
			    &__swapper_4m_tsb_phys_patch_end, ktsb_pa);
	}
#endif
}