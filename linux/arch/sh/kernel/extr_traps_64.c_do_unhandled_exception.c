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
 int /*<<< orphan*/  die_if_no_fixup (char*,struct pt_regs*,unsigned long) ; 
 int /*<<< orphan*/  force_sig (int) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static void do_unhandled_exception(int signr, char *str, unsigned long error,
				   struct pt_regs *regs)
{
	if (user_mode(regs))
		force_sig(signr);

	die_if_no_fixup(str, regs, error);
}