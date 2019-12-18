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
typedef  int /*<<< orphan*/  float64 ;
typedef  int /*<<< orphan*/  flag ;

/* Variables and functions */
 int /*<<< orphan*/  __fpu_setreg64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emul_trap (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  insn_float64_cmpe ; 

flag syst_float64_le(float64 a, float64 b)
{
	u_long r;

	__fpu_setreg64(0, a);
	__fpu_setreg64(2, b);
	emul_trap(&insn_float64_cmpe, 0x0UL);
	__asm __volatile("mov 0,%0; movle %%fcc0,1,%0" : "=r" (r));
	return (r);
}