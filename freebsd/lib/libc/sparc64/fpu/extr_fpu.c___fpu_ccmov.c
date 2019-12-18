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
typedef  int /*<<< orphan*/  u_int32_t ;
struct fpemu {int dummy; } ;

/* Variables and functions */
 int IF_F4_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __fpu_mov (struct fpemu*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
__fpu_ccmov(struct fpemu *fe, int type, int rd, int rs2,
    u_int32_t insn, int fcc)
{

	if (IF_F4_COND(insn) == fcc)
		__fpu_mov(fe, type, rd, rs2, 0, 0);
}