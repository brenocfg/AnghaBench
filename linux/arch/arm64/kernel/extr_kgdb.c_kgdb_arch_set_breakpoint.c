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
struct kgdb_bkpt {scalar_t__ bpt_addr; scalar_t__ saved_instr; } ;

/* Variables and functions */
 scalar_t__ AARCH64_BREAK_KGDB_DYN_DBG ; 
 scalar_t__ AARCH64_INSN_SIZE ; 
 scalar_t__ BREAK_INSTR_SIZE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int aarch64_insn_read (void*,int /*<<< orphan*/ *) ; 
 int aarch64_insn_write (void*,int /*<<< orphan*/ ) ; 

int kgdb_arch_set_breakpoint(struct kgdb_bkpt *bpt)
{
	int err;

	BUILD_BUG_ON(AARCH64_INSN_SIZE != BREAK_INSTR_SIZE);

	err = aarch64_insn_read((void *)bpt->bpt_addr, (u32 *)bpt->saved_instr);
	if (err)
		return err;

	return aarch64_insn_write((void *)bpt->bpt_addr,
			(u32)AARCH64_BREAK_KGDB_DYN_DBG);
}