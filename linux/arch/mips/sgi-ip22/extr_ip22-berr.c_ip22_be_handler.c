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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int MIPS_BE_FATAL ; 
 int MIPS_BE_FIXUP ; 
 int /*<<< orphan*/  print_buserr () ; 
 int /*<<< orphan*/  save_and_clear_buserr () ; 

__attribute__((used)) static int ip22_be_handler(struct pt_regs *regs, int is_fixup)
{
	save_and_clear_buserr();
	if (is_fixup)
		return MIPS_BE_FIXUP;
	print_buserr();
	return MIPS_BE_FATAL;
}