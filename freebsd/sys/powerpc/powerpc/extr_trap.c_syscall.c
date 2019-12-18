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
struct trapframe {int dummy; } ;
struct thread {TYPE_3__* td_pcb; struct trapframe* td_frame; } ;
struct TYPE_4__ {scalar_t__ usr_vsid; } ;
struct TYPE_5__ {TYPE_1__ aim; } ;
struct TYPE_6__ {TYPE_2__ pcb_cpu; } ;

/* Variables and functions */
 struct thread* curthread ; 
 int /*<<< orphan*/  syscallenter (struct thread*) ; 
 int /*<<< orphan*/  syscallret (struct thread*) ; 

void
syscall(struct trapframe *frame)
{
	struct thread *td;

	td = curthread;
	td->td_frame = frame;

#if defined(__powerpc64__) && defined(AIM)
	/*
	 * Speculatively restore last user SLB segment, which we know is
	 * invalid already, since we are likely to do copyin()/copyout().
	 */
	if (td->td_pcb->pcb_cpu.aim.usr_vsid != 0)
		__asm __volatile ("slbmte %0, %1; isync" ::
		    "r"(td->td_pcb->pcb_cpu.aim.usr_vsid), "r"(USER_SLB_SLBE));
#endif

	syscallenter(td);
	syscallret(td);
}