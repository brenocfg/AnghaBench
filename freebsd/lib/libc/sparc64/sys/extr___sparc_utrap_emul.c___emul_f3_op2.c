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
typedef  int /*<<< orphan*/  u_int ;
struct utrapframe {int dummy; } ;

/* Variables and functions */
 scalar_t__ IF_F3_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_F3_RS2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_SIMM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __emul_fetch_reg (struct utrapframe*,int /*<<< orphan*/ ) ; 

u_long
__emul_f3_op2(struct utrapframe *uf, u_int insn)
{

	if (IF_F3_I(insn) != 0)
		return (IF_SIMM(insn, 13));
	else
		return (__emul_fetch_reg(uf, IF_F3_RS2(insn)));
}