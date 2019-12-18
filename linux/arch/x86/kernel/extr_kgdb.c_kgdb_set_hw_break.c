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
typedef  enum kgdb_bptype { ____Placeholder_kgdb_bptype } kgdb_bptype ;
struct TYPE_2__ {int enabled; unsigned long addr; int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  BP_ACCESS_WATCHPOINT 130 
#define  BP_HARDWARE_BREAKPOINT 129 
#define  BP_WRITE_WATCHPOINT 128 
 int HBP_NUM ; 
 int /*<<< orphan*/  X86_BREAKPOINT_EXECUTE ; 
 int /*<<< orphan*/  X86_BREAKPOINT_LEN_1 ; 
 int /*<<< orphan*/  X86_BREAKPOINT_LEN_2 ; 
 int /*<<< orphan*/  X86_BREAKPOINT_LEN_4 ; 
 int /*<<< orphan*/  X86_BREAKPOINT_LEN_8 ; 
 int /*<<< orphan*/  X86_BREAKPOINT_RW ; 
 int /*<<< orphan*/  X86_BREAKPOINT_WRITE ; 
 TYPE_1__* breakinfo ; 
 scalar_t__ hw_break_reserve_slot (int) ; 

__attribute__((used)) static int
kgdb_set_hw_break(unsigned long addr, int len, enum kgdb_bptype bptype)
{
	int i;

	for (i = 0; i < HBP_NUM; i++)
		if (!breakinfo[i].enabled)
			break;
	if (i == HBP_NUM)
		return -1;

	switch (bptype) {
	case BP_HARDWARE_BREAKPOINT:
		len = 1;
		breakinfo[i].type = X86_BREAKPOINT_EXECUTE;
		break;
	case BP_WRITE_WATCHPOINT:
		breakinfo[i].type = X86_BREAKPOINT_WRITE;
		break;
	case BP_ACCESS_WATCHPOINT:
		breakinfo[i].type = X86_BREAKPOINT_RW;
		break;
	default:
		return -1;
	}
	switch (len) {
	case 1:
		breakinfo[i].len = X86_BREAKPOINT_LEN_1;
		break;
	case 2:
		breakinfo[i].len = X86_BREAKPOINT_LEN_2;
		break;
	case 4:
		breakinfo[i].len = X86_BREAKPOINT_LEN_4;
		break;
#ifdef CONFIG_X86_64
	case 8:
		breakinfo[i].len = X86_BREAKPOINT_LEN_8;
		break;
#endif
	default:
		return -1;
	}
	breakinfo[i].addr = addr;
	if (hw_break_reserve_slot(i)) {
		breakinfo[i].addr = 0;
		return -1;
	}
	breakinfo[i].enabled = 1;

	return 0;
}