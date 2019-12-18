#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int mask; int /*<<< orphan*/  addr; } ;
struct pt_regs {TYPE_2__ psw; } ;
struct TYPE_6__ {int cause; int /*<<< orphan*/  address; } ;
struct TYPE_9__ {int control; scalar_t__ end; scalar_t__ start; } ;
struct TYPE_8__ {TYPE_1__ per_event; TYPE_4__ per_user; } ;
struct TYPE_10__ {TYPE_3__ thread; } ;

/* Variables and functions */
 int PER_EVENT_STORE ; 
 int /*<<< orphan*/  PIF_PER_TRAP ; 
 int PSW_MASK_PER ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  set_pt_regs_flag (struct pt_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sim_stor_event(struct pt_regs *regs, void *addr, int len)
{
	if (!(regs->psw.mask & PSW_MASK_PER))
		return;
	if (!(current->thread.per_user.control & PER_EVENT_STORE))
		return;
	if ((void *)current->thread.per_user.start > (addr + len))
		return;
	if ((void *)current->thread.per_user.end < addr)
		return;
	current->thread.per_event.address = regs->psw.addr;
	current->thread.per_event.cause = PER_EVENT_STORE >> 16;
	set_pt_regs_flag(regs, PIF_PER_TRAP);
}