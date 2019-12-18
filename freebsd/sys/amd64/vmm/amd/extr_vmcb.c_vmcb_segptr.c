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
struct vmcb_segment {int dummy; } ;
struct vmcb_state {struct vmcb_segment tr; struct vmcb_segment ldt; struct vmcb_segment idt; struct vmcb_segment gdt; struct vmcb_segment ss; struct vmcb_segment gs; struct vmcb_segment fs; struct vmcb_segment es; struct vmcb_segment ds; struct vmcb_segment cs; } ;
struct vmcb {struct vmcb_state state; } ;

/* Variables and functions */
#define  VM_REG_GUEST_CS 137 
#define  VM_REG_GUEST_DS 136 
#define  VM_REG_GUEST_ES 135 
#define  VM_REG_GUEST_FS 134 
#define  VM_REG_GUEST_GDTR 133 
#define  VM_REG_GUEST_GS 132 
#define  VM_REG_GUEST_IDTR 131 
#define  VM_REG_GUEST_LDTR 130 
#define  VM_REG_GUEST_SS 129 
#define  VM_REG_GUEST_TR 128 

__attribute__((used)) static struct vmcb_segment *
vmcb_segptr(struct vmcb *vmcb, int type)
{
	struct vmcb_state *state;
	struct vmcb_segment *seg;

	state = &vmcb->state;

	switch (type) {
	case VM_REG_GUEST_CS:
		seg = &state->cs;
		break;

	case VM_REG_GUEST_DS:
		seg = &state->ds;
		break;

	case VM_REG_GUEST_ES:
		seg = &state->es;
		break;

	case VM_REG_GUEST_FS:
		seg = &state->fs;
		break;

	case VM_REG_GUEST_GS:
		seg = &state->gs;
		break;

	case VM_REG_GUEST_SS:
		seg = &state->ss;
		break;

	case VM_REG_GUEST_GDTR:
		seg = &state->gdt;
		break;

	case VM_REG_GUEST_IDTR:
		seg = &state->idt;
		break;

	case VM_REG_GUEST_LDTR:
		seg = &state->ldt;
		break;

	case VM_REG_GUEST_TR:
		seg = &state->tr;
		break;

	default:
		seg = NULL;
		break;
	}

	return (seg);
}