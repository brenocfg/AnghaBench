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
struct TYPE_2__ {unsigned long usp; scalar_t__ esp0; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 unsigned short CCR_MASK ; 
 unsigned short EXR_MASK ; 
#define  PT_CCR 130 
#define  PT_EXR 129 
#define  PT_USP 128 
 scalar_t__* register_offset ; 

int h8300_put_reg(struct task_struct *task, int regno, unsigned long data)
{
	unsigned short oldccr;
	unsigned short oldexr;

	switch (regno) {
	case PT_USP:
		task->thread.usp = data - sizeof(long)*2;
	case PT_CCR:
		oldccr = *(unsigned short *)(task->thread.esp0 +
					     register_offset[regno]);
		oldccr &= ~CCR_MASK;
		data &= CCR_MASK;
		data |= oldccr;
		*(unsigned short *)(task->thread.esp0 +
				    register_offset[regno]) = data;
		break;
	case PT_EXR:
		oldexr = *(unsigned short *)(task->thread.esp0 +
					     register_offset[regno]);
		oldccr &= ~EXR_MASK;
		data &= EXR_MASK;
		data |= oldexr;
		*(unsigned short *)(task->thread.esp0 +
				    register_offset[regno]) = data;
		break;
	default:
		*(unsigned long *)(task->thread.esp0 +
				   register_offset[regno]) = data;
		break;
	}
	return 0;
}