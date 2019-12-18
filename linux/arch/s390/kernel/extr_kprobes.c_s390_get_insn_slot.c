#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * insn; } ;
struct kprobe {TYPE_1__ ainsn; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * get_insn_slot () ; 
 int /*<<< orphan*/ * get_s390_insn_slot () ; 
 scalar_t__ is_kernel_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_module_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s390_get_insn_slot(struct kprobe *p)
{
	/*
	 * Get an insn slot that is within the same 2GB area like the original
	 * instruction. That way instructions with a 32bit signed displacement
	 * field can be patched and executed within the insn slot.
	 */
	p->ainsn.insn = NULL;
	if (is_kernel_addr(p->addr))
		p->ainsn.insn = get_s390_insn_slot();
	else if (is_module_addr(p->addr))
		p->ainsn.insn = get_insn_slot();
	return p->ainsn.insn ? 0 : -ENOMEM;
}