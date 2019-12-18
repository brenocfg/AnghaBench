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
struct task_struct {int dummy; } ;
struct switch_stack {int dummy; } ;
struct pt_regs {scalar_t__ ar_bspstore; } ;
typedef  int /*<<< orphan*/  ret ;

/* Variables and functions */
 long EIO ; 
 int /*<<< orphan*/  FOLL_FORCE ; 
 int IA64_RBS_OFFSET ; 
 size_t access_process_vm (struct task_struct*,unsigned long,long*,int,int /*<<< orphan*/ ) ; 
 long get_rnat (struct task_struct*,struct switch_stack*,unsigned long*,unsigned long*,unsigned long*) ; 
 unsigned long ia64_rse_num_regs (unsigned long*,unsigned long*) ; 
 unsigned long* ia64_rse_rnat_addr (unsigned long*) ; 
 long* ia64_rse_skip_regs (unsigned long*,unsigned long) ; 
 unsigned long ia64_rse_slot_num (unsigned long*) ; 
 scalar_t__ on_kernel_rbs (unsigned long,unsigned long,unsigned long) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

long
ia64_peek (struct task_struct *child, struct switch_stack *child_stack,
	   unsigned long user_rbs_end, unsigned long addr, long *val)
{
	unsigned long *bspstore, *krbs, regnum, *laddr, *urbs_end, *rnat_addr;
	struct pt_regs *child_regs;
	size_t copied;
	long ret;

	urbs_end = (long *) user_rbs_end;
	laddr = (unsigned long *) addr;
	child_regs = task_pt_regs(child);
	bspstore = (unsigned long *) child_regs->ar_bspstore;
	krbs = (unsigned long *) child + IA64_RBS_OFFSET/8;
	if (on_kernel_rbs(addr, (unsigned long) bspstore,
			  (unsigned long) urbs_end))
	{
		/*
		 * Attempt to read the RBS in an area that's actually
		 * on the kernel RBS => read the corresponding bits in
		 * the kernel RBS.
		 */
		rnat_addr = ia64_rse_rnat_addr(laddr);
		ret = get_rnat(child, child_stack, krbs, rnat_addr, urbs_end);

		if (laddr == rnat_addr) {
			/* return NaT collection word itself */
			*val = ret;
			return 0;
		}

		if (((1UL << ia64_rse_slot_num(laddr)) & ret) != 0) {
			/*
			 * It is implementation dependent whether the
			 * data portion of a NaT value gets saved on a
			 * st8.spill or RSE spill (e.g., see EAS 2.6,
			 * 4.4.4.6 Register Spill and Fill).  To get
			 * consistent behavior across all possible
			 * IA-64 implementations, we return zero in
			 * this case.
			 */
			*val = 0;
			return 0;
		}

		if (laddr < urbs_end) {
			/*
			 * The desired word is on the kernel RBS and
			 * is not a NaT.
			 */
			regnum = ia64_rse_num_regs(bspstore, laddr);
			*val = *ia64_rse_skip_regs(krbs, regnum);
			return 0;
		}
	}
	copied = access_process_vm(child, addr, &ret, sizeof(ret), FOLL_FORCE);
	if (copied != sizeof(ret))
		return -EIO;
	*val = ret;
	return 0;
}