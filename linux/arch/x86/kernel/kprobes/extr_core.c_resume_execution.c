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
struct pt_regs {unsigned long flags; unsigned long ip; } ;
struct kprobe_ctlblk {unsigned long kprobe_old_flags; } ;
struct TYPE_2__ {int* insn; int boostable; } ;
struct kprobe {TYPE_1__ ainsn; scalar_t__ addr; } ;
typedef  int kprobe_opcode_t ;

/* Variables and functions */
 unsigned long X86_EFLAGS_IF ; 
 unsigned long X86_EFLAGS_TF ; 
 int /*<<< orphan*/  restore_btf () ; 
 int* skip_prefixes (int*) ; 
 unsigned long* stack_addr (struct pt_regs*) ; 

__attribute__((used)) static void resume_execution(struct kprobe *p, struct pt_regs *regs,
			     struct kprobe_ctlblk *kcb)
{
	unsigned long *tos = stack_addr(regs);
	unsigned long copy_ip = (unsigned long)p->ainsn.insn;
	unsigned long orig_ip = (unsigned long)p->addr;
	kprobe_opcode_t *insn = p->ainsn.insn;

	/* Skip prefixes */
	insn = skip_prefixes(insn);

	regs->flags &= ~X86_EFLAGS_TF;
	switch (*insn) {
	case 0x9c:	/* pushfl */
		*tos &= ~(X86_EFLAGS_TF | X86_EFLAGS_IF);
		*tos |= kcb->kprobe_old_flags;
		break;
	case 0xc2:	/* iret/ret/lret */
	case 0xc3:
	case 0xca:
	case 0xcb:
	case 0xcf:
	case 0xea:	/* jmp absolute -- ip is correct */
		/* ip is already adjusted, no more changes required */
		p->ainsn.boostable = true;
		goto no_change;
	case 0xe8:	/* call relative - Fix return addr */
		*tos = orig_ip + (*tos - copy_ip);
		break;
#ifdef CONFIG_X86_32
	case 0x9a:	/* call absolute -- same as call absolute, indirect */
		*tos = orig_ip + (*tos - copy_ip);
		goto no_change;
#endif
	case 0xff:
		if ((insn[1] & 0x30) == 0x10) {
			/*
			 * call absolute, indirect
			 * Fix return addr; ip is correct.
			 * But this is not boostable
			 */
			*tos = orig_ip + (*tos - copy_ip);
			goto no_change;
		} else if (((insn[1] & 0x31) == 0x20) ||
			   ((insn[1] & 0x31) == 0x21)) {
			/*
			 * jmp near and far, absolute indirect
			 * ip is correct. And this is boostable
			 */
			p->ainsn.boostable = true;
			goto no_change;
		}
	default:
		break;
	}

	regs->ip += orig_ip - copy_ip;

no_change:
	restore_btf();
}