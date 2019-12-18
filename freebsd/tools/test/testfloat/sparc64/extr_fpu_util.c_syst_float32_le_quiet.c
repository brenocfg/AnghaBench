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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  float32 ;
typedef  int /*<<< orphan*/  flag ;

/* Variables and functions */
 int /*<<< orphan*/  __fpu_setreg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emul_trap (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  insn_float32_cmp ; 

flag syst_float32_le_quiet(float32 a, float32 b)
{
	u_long r;

	__fpu_setreg(0, a);
	__fpu_setreg(1, b);
	emul_trap(&insn_float32_cmp, 0x0UL);
	__asm __volatile("mov 0,%0; movle %%fcc0,1,%0" : "=r" (r));
	return (r);
}