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
struct reg_window32 {unsigned long* locals; } ;
struct pt_regs {unsigned long* u_regs; } ;

/* Variables and functions */
 size_t UREG_FP ; 

__attribute__((used)) static inline unsigned long *fetch_reg_addr(unsigned int reg, struct pt_regs *regs)
{
	struct reg_window32 *win;

	if(reg < 16)
		return &regs->u_regs[reg];
	win = (struct reg_window32 *) regs->u_regs[UREG_FP];
	return &win->locals[reg - 16];
}