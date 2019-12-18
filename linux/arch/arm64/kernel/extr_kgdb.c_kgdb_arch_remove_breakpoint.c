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
struct kgdb_bkpt {scalar_t__ saved_instr; scalar_t__ bpt_addr; } ;

/* Variables and functions */
 int aarch64_insn_write (void*,int /*<<< orphan*/ ) ; 

int kgdb_arch_remove_breakpoint(struct kgdb_bkpt *bpt)
{
	return aarch64_insn_write((void *)bpt->bpt_addr,
			*(u32 *)bpt->saved_instr);
}