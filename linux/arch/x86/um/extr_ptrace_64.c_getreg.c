#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long* gp; } ;
struct TYPE_5__ {TYPE_1__ regs; } ;
struct TYPE_6__ {TYPE_2__ regs; } ;
struct task_struct {TYPE_3__ thread; } ;

/* Variables and functions */
#define  CS 154 
#define  DS 153 
#define  EFLAGS 152 
#define  ES 151 
#define  FS 150 
#define  FS_BASE 149 
#define  GS 148 
#define  GS_BASE 147 
#define  ORIG_RAX 146 
#define  R10 145 
#define  R11 144 
#define  R12 143 
#define  R13 142 
#define  R14 141 
#define  R15 140 
#define  R8 139 
#define  R9 138 
#define  RAX 137 
#define  RBP 136 
#define  RBX 135 
#define  RCX 134 
#define  RDI 133 
#define  RDX 132 
#define  RIP 131 
#define  RSI 130 
#define  RSP 129 
#define  SS 128 
 int /*<<< orphan*/  TIF_IA32 ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 size_t* reg_offsets ; 
 scalar_t__ test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

unsigned long getreg(struct task_struct *child, int regno)
{
	unsigned long mask = ~0UL;
#ifdef TIF_IA32
	if (test_tsk_thread_flag(child, TIF_IA32))
		mask = 0xffffffff;
#endif
	switch (regno) {
	case R8:
	case R9:
	case R10:
	case R11:
	case R12:
	case R13:
	case R14:
	case R15:
	case RIP:
	case RSP:
	case RAX:
	case RBX:
	case RCX:
	case RDX:
	case RSI:
	case RDI:
	case RBP:
	case ORIG_RAX:
	case EFLAGS:
	case FS_BASE:
	case GS_BASE:
		break;
	case FS:
	case GS:
	case DS:
	case ES:
	case SS:
	case CS:
		mask = 0xffff;
		break;
	default:
		panic("Bad register in getreg: %d\n", regno);
	}
	return mask & child->thread.regs.regs.gp[reg_offsets[regno >> 3]];
}