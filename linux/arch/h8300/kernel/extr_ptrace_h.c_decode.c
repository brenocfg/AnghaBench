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
struct task_struct {int dummy; } ;
struct optable {int type; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_ER0 ; 
 int /*<<< orphan*/  PT_ER1 ; 
 int /*<<< orphan*/  PT_USP ; 
 unsigned long h8300_get_reg (struct task_struct*,int /*<<< orphan*/ ) ; 
#define  ind 134 
 int /*<<< orphan*/  isbranch (struct task_struct*,char) ; 
#define  jabs 133 
#define  none 132 
#define  reg 131 
#define  relb 130 
#define  relw 129 
#define  ret 128 

__attribute__((used)) static unsigned short *decode(struct task_struct *child,
			      const struct optable *op,
			      char *fetch_p, unsigned short *pc,
			      unsigned char inst)
{
	unsigned long addr;
	unsigned long *sp;
	int regno;

	switch (op->type) {
	case none:
		return (unsigned short *)pc + op->length;
	case jabs:
		addr = *(unsigned long *)pc;
		return (unsigned short *)(addr & 0x00ffffff);
	case ind:
		addr = *pc & 0xff;
		return (unsigned short *)(*(unsigned long *)addr);
	case ret:
		sp = (unsigned long *)h8300_get_reg(child, PT_USP);
		/* user stack frames
		   |   er0  | temporary saved
		   +--------+
		   |   exp  | exception stack frames
		   +--------+
		   | ret pc | userspace return address
		*/
		return (unsigned short *)(*(sp+2) & 0x00ffffff);
	case reg:
		regno = (*pc >> 4) & 0x07;
		if (regno == 0)
			addr = h8300_get_reg(child, PT_ER0);
		else
			addr = h8300_get_reg(child, regno-1 + PT_ER1);
		return (unsigned short *)addr;
	case relb:
		if (inst == 0x55 || isbranch(child, inst & 0x0f))
			pc = (unsigned short *)((unsigned long)pc +
						((signed char)(*fetch_p)));
		return pc+1; /* skip myself */
	case relw:
		if (inst == 0x5c || isbranch(child, (*fetch_p & 0xf0) >> 4))
			pc = (unsigned short *)((unsigned long)pc +
						((signed short)(*(pc+1))));
		return pc+2; /* skip myself */
	default:
		return NULL;
	}
}