#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_3__* mm; } ;
struct pt_regs {unsigned long ip; unsigned long cs; } ;
struct desc_struct {int /*<<< orphan*/  d; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_1__* ldt; } ;
struct TYPE_6__ {TYPE_2__ context; } ;
struct TYPE_4__ {unsigned long nr_entries; struct desc_struct* entries; } ;

/* Variables and functions */
 unsigned long SEGMENT_LDT ; 
 unsigned long SEGMENT_TI_MASK ; 
 unsigned long get_desc_base (struct desc_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ v8086_mode (struct pt_regs*) ; 

unsigned long convert_ip_to_linear(struct task_struct *child, struct pt_regs *regs)
{
	unsigned long addr, seg;

	addr = regs->ip;
	seg = regs->cs;
	if (v8086_mode(regs)) {
		addr = (addr & 0xffff) + (seg << 4);
		return addr;
	}

#ifdef CONFIG_MODIFY_LDT_SYSCALL
	/*
	 * We'll assume that the code segments in the GDT
	 * are all zero-based. That is largely true: the
	 * TLS segments are used for data, and the PNPBIOS
	 * and APM bios ones we just ignore here.
	 */
	if ((seg & SEGMENT_TI_MASK) == SEGMENT_LDT) {
		struct desc_struct *desc;
		unsigned long base;

		seg >>= 3;

		mutex_lock(&child->mm->context.lock);
		if (unlikely(!child->mm->context.ldt ||
			     seg >= child->mm->context.ldt->nr_entries))
			addr = -1L; /* bogus selector, access would fault */
		else {
			desc = &child->mm->context.ldt->entries[seg];
			base = get_desc_base(desc);

			/* 16-bit code segment? */
			if (!desc->d)
				addr &= 0xffff;
			addr += base;
		}
		mutex_unlock(&child->mm->context.lock);
	}
#endif

	return addr;
}