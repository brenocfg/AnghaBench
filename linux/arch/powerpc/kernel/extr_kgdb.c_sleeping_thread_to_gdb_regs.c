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
struct TYPE_2__ {int /*<<< orphan*/ * evr; scalar_t__ ksp; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int /*<<< orphan*/  xer; int /*<<< orphan*/  ctr; int /*<<< orphan*/  link; int /*<<< orphan*/  ccr; int /*<<< orphan*/  msr; int /*<<< orphan*/  nip; int /*<<< orphan*/ * gpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NUMREGBYTES ; 
 int /*<<< orphan*/  PACK32 (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACK64 (unsigned long*,int /*<<< orphan*/ ) ; 
 scalar_t__ STACK_FRAME_OVERHEAD ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int) ; 

void sleeping_thread_to_gdb_regs(unsigned long *gdb_regs, struct task_struct *p)
{
	struct pt_regs *regs = (struct pt_regs *)(p->thread.ksp +
						  STACK_FRAME_OVERHEAD);
	unsigned long *ptr = gdb_regs;
	int reg;

	memset(gdb_regs, 0, NUMREGBYTES);

	/* Regs GPR0-2 */
	for (reg = 0; reg < 3; reg++)
		PACK64(ptr, regs->gpr[reg]);

	/* Regs GPR3-13 are caller saved, not in regs->gpr[] */
	ptr += 11;

	/* Regs GPR14-31 */
	for (reg = 14; reg < 32; reg++)
		PACK64(ptr, regs->gpr[reg]);

#ifdef CONFIG_FSL_BOOKE
#ifdef CONFIG_SPE
	for (reg = 0; reg < 32; reg++)
		PACK64(ptr, p->thread.evr[reg]);
#else
	ptr += 32;
#endif
#else
	/* fp registers not used by kernel, leave zero */
	ptr += 32 * 8 / sizeof(long);
#endif

	PACK64(ptr, regs->nip);
	PACK64(ptr, regs->msr);
	PACK32(ptr, regs->ccr);
	PACK64(ptr, regs->link);
	PACK64(ptr, regs->ctr);
	PACK32(ptr, regs->xer);

	BUG_ON((unsigned long)ptr >
	       (unsigned long)(((void *)gdb_regs) + NUMREGBYTES));
}