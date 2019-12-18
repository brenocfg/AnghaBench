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
 int DBG_HOOK_HANDLED ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  kgdb_handle_exception (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pt_regs*) ; 

__attribute__((used)) static int kgdb_brk_fn(struct pt_regs *regs, unsigned int esr)
{
	kgdb_handle_exception(1, SIGTRAP, 0, regs);
	return DBG_HOOK_HANDLED;
}