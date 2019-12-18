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
 scalar_t__ KERNELBASE ; 
 scalar_t__ PHYSICAL_START ; 
 int __end_interrupts ; 
 int _stext ; 
 int /*<<< orphan*/  raw_patch_instruction (int*,int) ; 

__attribute__((used)) static void do_final_fixups(void)
{
#if defined(CONFIG_PPC64) && defined(CONFIG_RELOCATABLE)
	int *src, *dest;
	unsigned long length;

	if (PHYSICAL_START == 0)
		return;

	src = (int *)(KERNELBASE + PHYSICAL_START);
	dest = (int *)KERNELBASE;
	length = (__end_interrupts - _stext) / sizeof(int);

	while (length--) {
		raw_patch_instruction(dest, *src);
		src++;
		dest++;
	}
#endif
}