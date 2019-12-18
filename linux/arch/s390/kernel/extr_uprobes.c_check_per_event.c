#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int mask; scalar_t__ addr; } ;
struct pt_regs {TYPE_3__ psw; } ;
struct TYPE_5__ {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_6__ {TYPE_1__ per_user; } ;
struct TYPE_8__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int PSW_MASK_PER ; 
 TYPE_4__* current ; 

__attribute__((used)) static int check_per_event(unsigned short cause, unsigned long control,
			   struct pt_regs *regs)
{
	if (!(regs->psw.mask & PSW_MASK_PER))
		return 0;
	/* user space single step */
	if (control == 0)
		return 1;
	/* over indication for storage alteration */
	if ((control & 0x20200000) && (cause & 0x2000))
		return 1;
	if (cause & 0x8000) {
		/* all branches */
		if ((control & 0x80800000) == 0x80000000)
			return 1;
		/* branch into selected range */
		if (((control & 0x80800000) == 0x80800000) &&
		    regs->psw.addr >= current->thread.per_user.start &&
		    regs->psw.addr <= current->thread.per_user.end)
			return 1;
	}
	return 0;
}