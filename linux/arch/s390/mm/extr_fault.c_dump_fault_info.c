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
struct pt_regs {int int_parm_long; } ;
struct gmap {unsigned long asce; } ;
struct TYPE_2__ {unsigned long user_asce; unsigned long vdso_asce; unsigned long kernel_asce; scalar_t__ gmap; } ;

/* Variables and functions */
#define  GMAP_FAULT 131 
#define  KERNEL_FAULT 130 
 TYPE_1__ S390_lowcore ; 
#define  USER_FAULT 129 
#define  VDSO_FAULT 128 
 int __FAIL_ADDR_MASK ; 
 int /*<<< orphan*/  dump_pagetable (unsigned long,int) ; 
 int get_fault_type (struct pt_regs*) ; 
 int /*<<< orphan*/  pr_alert (char*,...) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  unreachable () ; 

__attribute__((used)) static void dump_fault_info(struct pt_regs *regs)
{
	unsigned long asce;

	pr_alert("Failing address: %016lx TEID: %016lx\n",
		 regs->int_parm_long & __FAIL_ADDR_MASK, regs->int_parm_long);
	pr_alert("Fault in ");
	switch (regs->int_parm_long & 3) {
	case 3:
		pr_cont("home space ");
		break;
	case 2:
		pr_cont("secondary space ");
		break;
	case 1:
		pr_cont("access register ");
		break;
	case 0:
		pr_cont("primary space ");
		break;
	}
	pr_cont("mode while using ");
	switch (get_fault_type(regs)) {
	case USER_FAULT:
		asce = S390_lowcore.user_asce;
		pr_cont("user ");
		break;
	case VDSO_FAULT:
		asce = S390_lowcore.vdso_asce;
		pr_cont("vdso ");
		break;
	case GMAP_FAULT:
		asce = ((struct gmap *) S390_lowcore.gmap)->asce;
		pr_cont("gmap ");
		break;
	case KERNEL_FAULT:
		asce = S390_lowcore.kernel_asce;
		pr_cont("kernel ");
		break;
	default:
		unreachable();
	}
	pr_cont("ASCE.\n");
	dump_pagetable(asce, regs->int_parm_long & __FAIL_ADDR_MASK);
}