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
struct TYPE_2__ {int size; int offset; char* name; } ;

/* Variables and functions */
 int DBG_MAX_REG_NUM ; 
#define  GDB_VBR 128 
 TYPE_1__* dbg_reg_def ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

char *dbg_get_reg(int regno, void *mem, struct pt_regs *regs)
{
	if (regno >= DBG_MAX_REG_NUM || regno < 0)
		return NULL;

	if (dbg_reg_def[regno].size != -1)
		memcpy(mem, (void *)regs + dbg_reg_def[regno].offset,
		       dbg_reg_def[regno].size);

	switch (regno) {
	case GDB_VBR:
		__asm__ __volatile__ ("stc vbr, %0" : "=r" (mem));
		break;
	}

	return dbg_reg_def[regno].name;
}