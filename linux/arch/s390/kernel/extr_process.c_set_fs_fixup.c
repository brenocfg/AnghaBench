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
struct pt_regs {int /*<<< orphan*/  int_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  USER_DS ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_registers (struct pt_regs*) ; 

void set_fs_fixup(void)
{
	struct pt_regs *regs = current_pt_regs();
	static bool warned;

	set_fs(USER_DS);
	if (warned)
		return;
	WARN(1, "Unbalanced set_fs - int code: 0x%x\n", regs->int_code);
	show_registers(regs);
	warned = true;
}