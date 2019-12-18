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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;
struct elf_prstatus {int /*<<< orphan*/  pr_reg; } ;
typedef  int /*<<< orphan*/  prstatus ;

/* Variables and functions */
 int /*<<< orphan*/  CRASH_CORE_NOTE_NAME ; 
 int /*<<< orphan*/  NT_PRSTATUS ; 
 int /*<<< orphan*/ * append_elf_note (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct elf_prstatus*,int) ; 
 int /*<<< orphan*/  elf_core_copy_kernel_regs (int /*<<< orphan*/ *,struct pt_regs*) ; 
 int /*<<< orphan*/  memset (struct elf_prstatus*,int /*<<< orphan*/ ,int) ; 

u32 *fadump_regs_to_elf_notes(u32 *buf, struct pt_regs *regs)
{
	struct elf_prstatus prstatus;

	memset(&prstatus, 0, sizeof(prstatus));
	/*
	 * FIXME: How do i get PID? Do I really need it?
	 * prstatus.pr_pid = ????
	 */
	elf_core_copy_kernel_regs(&prstatus.pr_reg, regs);
	buf = append_elf_note(buf, CRASH_CORE_NOTE_NAME, NT_PRSTATUS,
			      &prstatus, sizeof(prstatus));
	return buf;
}