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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int offset; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int GDB_FS ; 
 int GDB_GS ; 
 int GDB_ORIG_AX ; 
 int GDB_SP ; 
 int GDB_SS ; 
 TYPE_1__* dbg_reg_def ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

int dbg_set_reg(int regno, void *mem, struct pt_regs *regs)
{
	if (
#ifdef CONFIG_X86_32
	    regno == GDB_SS || regno == GDB_FS || regno == GDB_GS ||
#endif
	    regno == GDB_SP || regno == GDB_ORIG_AX)
		return 0;

	if (dbg_reg_def[regno].offset != -1)
		memcpy((void *)regs + dbg_reg_def[regno].offset, mem,
		       dbg_reg_def[regno].size);
	return 0;
}