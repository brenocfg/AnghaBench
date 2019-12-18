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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 unsigned long X86_CR0_EM ; 
 unsigned long X86_CR0_TS ; 

__attribute__((used)) static int has_fpu(void)
{
	u16 fcw = -1, fsw = -1;
	unsigned long cr0;

	asm volatile("mov %%cr0,%0" : "=r" (cr0));
	if (cr0 & (X86_CR0_EM|X86_CR0_TS)) {
		cr0 &= ~(X86_CR0_EM|X86_CR0_TS);
		asm volatile("mov %0,%%cr0" : : "r" (cr0));
	}

	asm volatile("fninit ; fnstsw %0 ; fnstcw %1"
		     : "+m" (fsw), "+m" (fcw));

	return fsw == 0 && (fcw & 0x103f) == 0x003f;
}