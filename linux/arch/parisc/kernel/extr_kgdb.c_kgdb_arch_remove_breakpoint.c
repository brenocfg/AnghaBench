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
struct kgdb_bkpt {int /*<<< orphan*/  saved_instr; scalar_t__ bpt_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __patch_text (void*,unsigned int) ; 

int kgdb_arch_remove_breakpoint(struct kgdb_bkpt *bpt)
{
	__patch_text((void *)bpt->bpt_addr, *(unsigned int *)&bpt->saved_instr);
	return 0;
}