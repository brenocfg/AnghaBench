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
struct pt_regs {int /*<<< orphan*/  cs; int /*<<< orphan*/  ip; } ;
struct mce {scalar_t__ finished; int /*<<< orphan*/  cs; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_machine_check (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void raise_exception(struct mce *m, struct pt_regs *pregs)
{
	struct pt_regs regs;
	unsigned long flags;

	if (!pregs) {
		memset(&regs, 0, sizeof(struct pt_regs));
		regs.ip = m->ip;
		regs.cs = m->cs;
		pregs = &regs;
	}
	/* in mcheck exeception handler, irq will be disabled */
	local_irq_save(flags);
	do_machine_check(pregs, 0);
	local_irq_restore(flags);
	m->finished = 0;
}