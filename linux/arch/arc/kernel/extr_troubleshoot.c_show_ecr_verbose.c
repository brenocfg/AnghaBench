#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {unsigned int ecr_vec; unsigned int ecr_cause; int ecr_param; int /*<<< orphan*/  ret; int /*<<< orphan*/  event; } ;
struct TYPE_3__ {unsigned long fault_address; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ISA_ARCOMPACT ; 
 unsigned int ECR_C_PROTV_INST_FETCH ; 
 unsigned int ECR_C_PROTV_MISALIG_DATA ; 
 unsigned int ECR_V_DTLB_MISS ; 
 unsigned int ECR_V_INSN_ERR ; 
 unsigned int ECR_V_ITLB_MISS ; 
 unsigned int ECR_V_MACH_CHK ; 
 unsigned int ECR_V_MEM_ERR ; 
 unsigned int ECR_V_MISALIGN ; 
 unsigned int ECR_V_PROTV ; 
 unsigned int ECR_V_TRAP ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_ecr_verbose(struct pt_regs *regs)
{
	unsigned int vec, cause_code;
	unsigned long address;

	pr_info("\n[ECR   ]: 0x%08lx => ", regs->event);

	/* For Data fault, this is data address not instruction addr */
	address = current->thread.fault_address;

	vec = regs->ecr_vec;
	cause_code = regs->ecr_cause;

	/* For DTLB Miss or ProtV, display the memory involved too */
	if (vec == ECR_V_DTLB_MISS) {
		pr_cont("Invalid %s @ 0x%08lx by insn @ 0x%08lx\n",
		       (cause_code == 0x01) ? "Read" :
		       ((cause_code == 0x02) ? "Write" : "EX"),
		       address, regs->ret);
	} else if (vec == ECR_V_ITLB_MISS) {
		pr_cont("Insn could not be fetched\n");
	} else if (vec == ECR_V_MACH_CHK) {
		pr_cont("Machine Check (%s)\n", (cause_code == 0x0) ?
					"Double Fault" : "Other Fatal Err");

	} else if (vec == ECR_V_PROTV) {
		if (cause_code == ECR_C_PROTV_INST_FETCH)
			pr_cont("Execute from Non-exec Page\n");
		else if (cause_code == ECR_C_PROTV_MISALIG_DATA &&
		         IS_ENABLED(CONFIG_ISA_ARCOMPACT))
			pr_cont("Misaligned r/w from 0x%08lx\n", address);
		else
			pr_cont("%s access not allowed on page\n",
				(cause_code == 0x01) ? "Read" :
				((cause_code == 0x02) ? "Write" : "EX"));
	} else if (vec == ECR_V_INSN_ERR) {
		pr_cont("Illegal Insn\n");
#ifdef CONFIG_ISA_ARCV2
	} else if (vec == ECR_V_MEM_ERR) {
		if (cause_code == 0x00)
			pr_cont("Bus Error from Insn Mem\n");
		else if (cause_code == 0x10)
			pr_cont("Bus Error from Data Mem\n");
		else
			pr_cont("Bus Error, check PRM\n");
	} else if (vec == ECR_V_MISALIGN) {
		pr_cont("Misaligned r/w from 0x%08lx\n", address);
#endif
	} else if (vec == ECR_V_TRAP) {
		if (regs->ecr_param == 5)
			pr_cont("gcc generated __builtin_trap\n");
	} else {
		pr_cont("Check Programmer's Manual\n");
	}
}