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
struct pt_insn_ext {int iclass; } ;
struct pt_insn {int dummy; } ;

/* Variables and functions */
#define  PTI_INST_INT 136 
#define  PTI_INST_INT1 135 
#define  PTI_INST_INT3 134 
#define  PTI_INST_INTO 133 
#define  PTI_INST_IRET 132 
#define  PTI_INST_SYSCALL 131 
#define  PTI_INST_SYSENTER 130 
#define  PTI_INST_SYSEXIT 129 
#define  PTI_INST_SYSRET 128 

int pt_insn_changes_cpl(const struct pt_insn *insn,
			const struct pt_insn_ext *iext)
{
	(void) insn;

	if (!iext)
		return 0;

	switch (iext->iclass) {
	default:
		return 0;

	case PTI_INST_INT:
	case PTI_INST_INT3:
	case PTI_INST_INT1:
	case PTI_INST_INTO:
	case PTI_INST_IRET:
	case PTI_INST_SYSCALL:
	case PTI_INST_SYSENTER:
	case PTI_INST_SYSEXIT:
	case PTI_INST_SYSRET:
		return 1;
	}
}