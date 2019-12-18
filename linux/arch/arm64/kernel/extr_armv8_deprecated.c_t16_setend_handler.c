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
typedef  int u32 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm64_skip_faulting_instruction (struct pt_regs*,int) ; 
 int compat_setend_handler (struct pt_regs*,int) ; 

__attribute__((used)) static int t16_setend_handler(struct pt_regs *regs, u32 instr)
{
	int rc = compat_setend_handler(regs, (instr >> 3) & 1);
	arm64_skip_faulting_instruction(regs, 2);
	return rc;
}