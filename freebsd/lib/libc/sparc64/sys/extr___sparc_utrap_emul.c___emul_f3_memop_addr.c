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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct utrapframe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_F3_RS1 (int /*<<< orphan*/ ) ; 
 scalar_t__ __emul_f3_op2 (struct utrapframe*,int /*<<< orphan*/ ) ; 
 scalar_t__ __emul_fetch_reg (struct utrapframe*,int /*<<< orphan*/ ) ; 

u_long
__emul_f3_memop_addr(struct utrapframe *uf, u_int insn)
{
	u_long addr;

	addr = __emul_f3_op2(uf, insn) + __emul_fetch_reg(uf, IF_F3_RS1(insn));
	return (addr);
}