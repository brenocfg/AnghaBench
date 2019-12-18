#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fprs; int /*<<< orphan*/  fpc; } ;
struct TYPE_7__ {int /*<<< orphan*/  mask; } ;
struct TYPE_11__ {int /*<<< orphan*/  per_info; TYPE_2__ fp_regs; int /*<<< orphan*/  orig_gpr2; int /*<<< orphan*/ * acrs; TYPE_1__ psw; } ;
struct user {TYPE_5__ regs; } ;
struct TYPE_9__ {scalar_t__ fprs; scalar_t__ vxrs; scalar_t__ fpc; } ;
struct TYPE_10__ {unsigned int* acrs; TYPE_3__ fpu; } ;
struct task_struct {TYPE_4__ thread; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_12__ {scalar_t__ orig_gpr2; int /*<<< orphan*/  psw; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int EINVAL ; 
 scalar_t__ MACHINE_HAS_VX ; 
 scalar_t__ PSW_ASC_HOME ; 
 scalar_t__ PSW_MASK_ASC ; 
 scalar_t__ PSW_MASK_BA ; 
 scalar_t__ PSW_MASK_EA ; 
 unsigned long PSW_MASK_RI ; 
 unsigned long PSW_MASK_USER ; 
 scalar_t__ PSW_USER_BITS ; 
 int /*<<< orphan*/  __poke_user_per (struct task_struct*,scalar_t__,scalar_t__) ; 
 scalar_t__ is_ri_task (struct task_struct*) ; 
 TYPE_6__* task_pt_regs (struct task_struct*) ; 
 scalar_t__ test_fp_ctl (scalar_t__) ; 

__attribute__((used)) static int __poke_user(struct task_struct *child, addr_t addr, addr_t data)
{
	struct user *dummy = NULL;
	addr_t offset;

	if (addr < (addr_t) &dummy->regs.acrs) {
		/*
		 * psw and gprs are stored on the stack
		 */
		if (addr == (addr_t) &dummy->regs.psw.mask) {
			unsigned long mask = PSW_MASK_USER;

			mask |= is_ri_task(child) ? PSW_MASK_RI : 0;
			if ((data ^ PSW_USER_BITS) & ~mask)
				/* Invalid psw mask. */
				return -EINVAL;
			if ((data & PSW_MASK_ASC) == PSW_ASC_HOME)
				/* Invalid address-space-control bits */
				return -EINVAL;
			if ((data & PSW_MASK_EA) && !(data & PSW_MASK_BA))
				/* Invalid addressing mode bits */
				return -EINVAL;
		}
		*(addr_t *)((addr_t) &task_pt_regs(child)->psw + addr) = data;

	} else if (addr < (addr_t) (&dummy->regs.orig_gpr2)) {
		/*
		 * access registers are stored in the thread structure
		 */
		offset = addr - (addr_t) &dummy->regs.acrs;
		/*
		 * Very special case: old & broken 64 bit gdb writing
		 * to acrs[15] with a 64 bit value. Ignore the lower
		 * half of the value and write the upper 32 bit to
		 * acrs[15]. Sick...
		 */
		if (addr == (addr_t) &dummy->regs.acrs[15])
			child->thread.acrs[15] = (unsigned int) (data >> 32);
		else
			*(addr_t *)((addr_t) &child->thread.acrs + offset) = data;

	} else if (addr == (addr_t) &dummy->regs.orig_gpr2) {
		/*
		 * orig_gpr2 is stored on the kernel stack
		 */
		task_pt_regs(child)->orig_gpr2 = data;

	} else if (addr < (addr_t) &dummy->regs.fp_regs) {
		/*
		 * prevent writes of padding hole between
		 * orig_gpr2 and fp_regs on s390.
		 */
		return 0;

	} else if (addr == (addr_t) &dummy->regs.fp_regs.fpc) {
		/*
		 * floating point control reg. is in the thread structure
		 */
		if ((unsigned int) data != 0 ||
		    test_fp_ctl(data >> (BITS_PER_LONG - 32)))
			return -EINVAL;
		child->thread.fpu.fpc = data >> (BITS_PER_LONG - 32);

	} else if (addr < (addr_t) (&dummy->regs.fp_regs + 1)) {
		/*
		 * floating point regs. are either in child->thread.fpu
		 * or the child->thread.fpu.vxrs array
		 */
		offset = addr - (addr_t) &dummy->regs.fp_regs.fprs;
		if (MACHINE_HAS_VX)
			*(addr_t *)((addr_t)
				child->thread.fpu.vxrs + 2*offset) = data;
		else
			*(addr_t *)((addr_t)
				child->thread.fpu.fprs + offset) = data;

	} else if (addr < (addr_t) (&dummy->regs.per_info + 1)) {
		/*
		 * Handle access to the per_info structure.
		 */
		addr -= (addr_t) &dummy->regs.per_info;
		__poke_user_per(child, addr, data);

	}

	return 0;
}